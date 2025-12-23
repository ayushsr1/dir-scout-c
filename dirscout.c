#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define MAX_LINE 256

void scan(const char *base_url, const char *wordlist) {
    FILE *file = fopen(wordlist, "r");
    if (!file) {
        perror("Failed to open wordlist");
        return;
    }

    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Failed to init curl\n");
        fclose(file);
        return;
    }

    char line[MAX_LINE];
    char url[1024];

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // remove newline
        snprintf(url, sizeof(url), "%s/%s", base_url, line);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);  // HEAD request
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 0L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            long status;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);
            if (status == 200 || status == 301 || status == 302 || status == 403) {
                printf("[+] %s --> %ld\n", url, status);
            }
        }
    }

    curl_easy_cleanup(curl);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <url> <wordlist>\n", argv[0]);
        return 1;
    }

    curl_global_init(CURL_GLOBAL_ALL);
    scan(argv[1], argv[2]);
    curl_global_cleanup();

    return 0;
}
