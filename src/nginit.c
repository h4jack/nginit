#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <direct.h>     // for _mkdir #windows
#include <io.h>         // For _access
#include <errno.h>      // For errno
#include <sys/stat.h>   // for mkdir #linux
#include <sys/types.h>
#include <dirent.h>


#define print printf
#define and &&
#define or ||
#define not !
#define is ==


#ifdef _WIN32
#define MKDIR(path) _mkdir(path)
#else
#define MKDIR(path) mkdir(path, 0755)
#endif


void print_help(){
        print("nginit:\n");
        print("    init, config and log files for nginx, this is nginit, nginx initialization.\n");
        print("[Version] nginit: v1.0\n");
        print("[Usage]: nginit [Project Path] -l\n");
        print("    [Project Path] project path is where your website code exists.. like source code of your site..\n");
        print("    [Config Path] config path is where nginx config file, i mean the required file exist's, whithout the files the nginx will not run properly..\n    e.g: config/nginx.conf\n    e.g: logs/error.log\n\n");
        print("[Example]: \n");
        print("    nginit\n");
        print("    nginit -cp c:/app/nginx-1.26.x\n");
        print("    nginit -l\n");
        print("    nginit -cp c:/app/nginx-1.26.x -l\n\n");
        print("\n");
        print("Build by: github@h4jack");
}

void print_error(char message[]){
    print("%s\n", message);
    print_help();
}

void move_to_html() {
    // Create the directory if it doesn't exist
    if (_mkdir("html") == -1) {
        // Check if the directory already exists
        if (errno != EEXIST) {
            perror("[Error] While creating html folder");
            return;  // Exit function on error
        }
        // Directory already exists
        printf("[File Created] ./html folder already exists.\n");
    } else {
        // Directory was created
        printf("[File Created] ./html folder created.\n");
    }

    // Move files and directories into the html directory excluding specific items
    const char *cmd = "for /D %F in (*) do @if not \"%F\"==\"conf\" if not \"%F\"==\"temp\" if not \"%F\"==\"logs\" if not \"%F\"==\".gitignore\" if not \"%F\"==\"README.md\" if not \"%F:~0,1%\"==\".\" move \"%F\" html\\ & for %G in (*.*) do @if not \"%G\"==\"conf\" if not \"%G\"==\"temp\" if not \"%G\"==\"logs\" if not \"%G\"==\".gitignore\" if not \"%G\"==\"README.md\" if not \"%G:~0,1%\"==\".\" move \"%G\" html\\";

    // Execute the move command
    int ret = system(cmd);
    if (ret == -1) {
        perror("[Error] While moving files and directories to html folder");
    } else {
        printf("[Success] Files and directories moved to html folder.\n");
    }
}

void fastcgi_params(){
    // Create and open the HTML file
    FILE *fp = fopen("conf/fastcgi_params", "w");
    if (fp == NULL) {
        perror("[Error] While creating conf/fastcgi_conf file");
        return;  // Exit function on error
    }

    // Write HTML content to the file
    fprintf(fp, "\n"
                "fastcgi_param  QUERY_STRING       $query_string;\n"
                "fastcgi_param  REQUEST_METHOD     $request_method;\n"
                "fastcgi_param  CONTENT_TYPE       $content_type;\n"
                "fastcgi_param  CONTENT_LENGTH     $content_length;\n"
                "\n"
                "fastcgi_param  SCRIPT_NAME        $fastcgi_script_name;\n"
                "fastcgi_param  REQUEST_URI        $request_uri;\n"
                "fastcgi_param  DOCUMENT_URI       $document_uri;\n"
                "fastcgi_param  DOCUMENT_ROOT      $document_root;\n"
                "fastcgi_param  SERVER_PROTOCOL    $server_protocol;\n"
                "fastcgi_param  REQUEST_SCHEME     $scheme;\n"
                "fastcgi_param  HTTPS              $https if_not_empty;\n"
                "\n"
                "fastcgi_param  GATEWAY_INTERFACE  CGI/1.1;\n"
                "fastcgi_param  SERVER_SOFTWARE    nginx/$nginx_version;\n"
                "\n"
                "fastcgi_param  REMOTE_ADDR        $remote_addr;\n"
                "fastcgi_param  REMOTE_PORT        $remote_port;\n"
                "fastcgi_param  SERVER_ADDR        $server_addr;\n"
                "fastcgi_param  SERVER_PORT        $server_port;\n"
                "fastcgi_param  SERVER_NAME        $server_name;\n"
                "\n"
                "# PHP only, required if PHP was built with --enable-force-cgi-redirect\n"
                "fastcgi_param  REDIRECT_STATUS    200;\n"
                "\n");

    // Close the file
    if (fclose(fp) != 0) {
        perror("[Error] While closing conf/fastcgi_params file");
        return;  // Exit function on error
    }

    printf("[File Created] conf/fastcgi_params file created.\n");
}

void fastcgi_conf(){
    // Create and open the HTML file
    FILE *fp = fopen("conf/fastcgi.conf", "w");
    if (fp == NULL) {
        perror("[Error] While creating conf/fastcgi.conf file");
        return;  // Exit function on error
    }

    // Write HTML content to the file
    fprintf(fp, "\n"
                "fastcgi_param  SCRIPT_FILENAME    $document_root$fastcgi_script_name;\n"
                "fastcgi_param  QUERY_STRING       $query_string;\n"
                "fastcgi_param  REQUEST_METHOD     $request_method;\n"
                "fastcgi_param  CONTENT_TYPE       $content_type;\n"
                "fastcgi_param  CONTENT_LENGTH     $content_length;\n"
                "\n"
                "fastcgi_param  SCRIPT_NAME        $fastcgi_script_name;\n"
                "fastcgi_param  REQUEST_URI        $request_uri;\n"
                "fastcgi_param  DOCUMENT_URI       $document_uri;\n"
                "fastcgi_param  DOCUMENT_ROOT      $document_root;\n"
                "fastcgi_param  SERVER_PROTOCOL    $server_protocol;\n"
                "fastcgi_param  REQUEST_SCHEME     $scheme;\n"
                "fastcgi_param  HTTPS              $https if_not_empty;\n"
                "\n"
                "fastcgi_param  GATEWAY_INTERFACE  CGI/1.1;\n"
                "fastcgi_param  SERVER_SOFTWARE    nginx/$nginx_version;\n"
                "\n"
                "fastcgi_param  REMOTE_ADDR        $remote_addr;\n"
                "fastcgi_param  REMOTE_PORT        $remote_port;\n"
                "fastcgi_param  SERVER_ADDR        $server_addr;\n"
                "fastcgi_param  SERVER_PORT        $server_port;\n"
                "fastcgi_param  SERVER_NAME        $server_name;\n"
                "\n"
                "# PHP only, required if PHP was built with --enable-force-cgi-redirect\n"
                "fastcgi_param  REDIRECT_STATUS    200;\n");
    // Close the file
    if (fclose(fp) != 0) {
        perror("[Error] While closing conf/fastcgi.conf file");
        return;  // Exit function on error
    }

    printf("[File Created] conf/fastcgi.conf file created.\n");
}

void koi_utf(){
    // Create and open the HTML file
    FILE *fp = fopen("conf/koi-utf", "w");
    if (fp == NULL) {
        perror("[Error] While creating conf/koi-utf file");
        return;  // Exit function on error
    }

    // Write HTML content to the file
    fprintf(fp, "\n"
                "# This map is not a full koi8-r <> utf8 map: it does not contain\n"
                "# box-drawing and some other characters.  Besides this map contains\n"
                "# several koi8-u and Byelorussian letters which are not in koi8-r.\n"
                "# If you need a full and standard map, use contrib/unicode2nginx/koi-utf\n"
                "# map instead.\n"
                "\n"
                "charset_map  koi8-r  utf-8 {\n"
                "\n"
                "    80  E282AC ; # euro\n"
                "\n"
                "    95  E280A2 ; # bullet\n"
                "\n"
                "    9A  C2A0 ;   # &nbsp;\n"
                "\n"
                "    9E  C2B7 ;   # &middot;\n"
                "\n"
                "    A3  D191 ;   # small yo\n"
                "    A4  D194 ;   # small Ukrainian ye\n"
                "\n"
                "    A6  D196 ;   # small Ukrainian i\n"
                "    A7  D197 ;   # small Ukrainian yi\n"
                "\n"
                "    AD  D291 ;   # small Ukrainian soft g\n"
                "    AE  D19E ;   # small Byelorussian short u\n"
                "\n"
                "    B0  C2B0 ;   # &deg;\n"
                "\n"
                "    B3  D081 ;   # capital YO\n"
                "    B4  D084 ;   # capital Ukrainian YE\n"
                "\n"
                "    B6  D086 ;   # capital Ukrainian I\n"
                "    B7  D087 ;   # capital Ukrainian YI\n"
                "\n"
                "    B9  E28496 ; # numero sign\n"
                "\n"
                "    BD  D290 ;   # capital Ukrainian soft G\n"
                "    BE  D18E ;   # capital Byelorussian short U\n"
                "\n"
                "    BF  C2A9 ;   # (C)\n"
                "\n"
                "    C0  D18E ;   # small yu\n"
                "    C1  D0B0 ;   # small a\n"
                "    C2  D0B1 ;   # small b\n"
                "    C3  D186 ;   # small ts\n"
                "    C4  D0B4 ;   # small d\n"
                "    C5  D0B5 ;   # small ye\n"
                "    C6  D184 ;   # small f\n"
                "    C7  D0B3 ;   # small g\n"
                "    C8  D185 ;   # small kh\n"
                "    C9  D0B8 ;   # small i\n"
                "    CA  D0B9 ;   # small j\n"
                "    CB  D0BA ;   # small k\n"
                "    CC  D0BB ;   # small l\n"
                "    CD  D0BC ;   # small m\n"
                "    CE  D0BD ;   # small n\n"
                "    CF  D0BE ;   # small o\n"
                "\n"
                "    D0  D0BF ;   # small p\n"
                "    D1  D18F ;   # small ya\n"
                "    D2  D180 ;   # small r\n"
                "    D3  D181 ;   # small s\n"
                "    D4  D182 ;   # small t\n"
                "    D5  D183 ;   # small u\n"
                "    D6  D0B6 ;   # small zh\n"
                "    D7  D0B2 ;   # small v\n"
                "    D8  D18C ;   # small soft sign\n"
                "    D9  D18B ;   # small y\n"
                "    DA  D0B7 ;   # small z\n"
                "    DB  D188 ;   # small sh\n"
                "    DC  D18D ;   # small e\n"
                "    DD  D189 ;   # small shch\n"
                "    DE  D187 ;   # small ch\n"
                "    DF  D18A ;   # small hard sign\n"
                "\n"
                "    E0  D0AE ;   # capital YU\n"
                "    E1  D090 ;   # capital A\n"
                "    E2  D091 ;   # capital B\n"
                "    E3  D0A6 ;   # capital TS\n"
                "    E4  D094 ;   # capital D\n"
                "    E5  D095 ;   # capital YE\n"
                "    E6  D0A4 ;   # capital F\n"
                "    E7  D093 ;   # capital G\n"
                "    E8  D0A5 ;   # capital KH\n"
                "    E9  D098 ;   # capital I\n"
                "    EA  D099 ;   # capital J\n"
                "    EB  D09A ;   # capital K\n"
                "    EC  D09B ;   # capital L\n"
                "    ED  D09C ;   # capital M\n"
                "    EE  D09D ;   # capital N\n"
                "    EF  D09E ;   # capital O\n"
                "\n"
                "    F0  D09F ;   # capital P\n"
                "    F1  D0AF ;   # capital YA\n"
                "    F2  D0A0 ;   # capital R\n"
                "    F3  D0A1 ;   # capital S\n"
                "    F4  D0A2 ;   # capital T\n"
                "    F5  D0A3 ;   # capital U\n"
                "    F6  D096 ;   # capital ZH\n"
                "    F7  D092 ;   # capital V\n"
                "    F8  D0AC ;   # capital soft sign\n"
                "    F9  D0AB ;   # capital Y\n"
                "    FA  D097 ;   # capital Z\n"
                "    FB  D0A8 ;   # capital SH\n"
                "    FC  D0AD ;   # capital E\n"
                "    FD  D0A9 ;   # capital SHCH\n"
                "    FE  D0A7 ;   # capital CH\n"
                "    FF  D0AA ;   # capital hard sign\n"
                "}\n");

    // Close the file
    if (fclose(fp) != 0) {
        perror("[Error] While closing conf/koi-utf file");
        return;  // Exit function on error
    }

    printf("[File Created] conf/koi-utf file created.\n");
}

void koi_win(){
    // Create and open the HTML file
    FILE *fp = fopen("conf/koi-win", "w");
    if (fp == NULL) {
        perror("[Error] While creating conf/koi-win file");
        return;  // Exit function on error
    }

    // Write HTML content to the file
    fprintf(fp, "\n"
                "charset_map  koi8-r  windows-1251 {\n"
                "\n"
                "    80  88 ; # euro\n"
                "\n"
                "    95  95 ; # bullet\n"
                "\n"
                "    9A  A0 ; # &nbsp;\n"
                "\n"
                "    9E  B7 ; # &middot;\n"
                "\n"
                "    A3  B8 ; # small yo\n"
                "    A4  BA ; # small Ukrainian ye\n"
                "\n"
                "    A6  B3 ; # small Ukrainian i\n"
                "    A7  BF ; # small Ukrainian yi\n"
                "\n"
                "    AD  B4 ; # small Ukrainian soft g\n"
                "    AE  A2 ; # small Byelorussian short u\n"
                "\n"
                "    B0  B0 ; # &deg;\n"
                "\n"
                "    B3  A8 ; # capital YO\n"
                "    B4  AA ; # capital Ukrainian YE\n"
                "\n"
                "    B6  B2 ; # capital Ukrainian I\n"
                "    B7  AF ; # capital Ukrainian YI\n"
                "\n"
                "    B9  B9 ; # numero sign\n"
                "\n"
                "    BD  A5 ; # capital Ukrainian soft G\n"
                "    BE  A1 ; # capital Byelorussian short U\n"
                "\n"
                "    BF  A9 ; # (C)\n"
                "\n"
                "    C0  FE ; # small yu\n"
                "    C1  E0 ; # small a\n"
                "    C2  E1 ; # small b\n"
                "    C3  F6 ; # small ts\n"
                "    C4  E4 ; # small d\n"
                "    C5  E5 ; # small ye\n"
                "    C6  F4 ; # small f\n"
                "    C7  E3 ; # small g\n"
                "    C8  F5 ; # small kh\n"
                "    C9  E8 ; # small i\n"
                "    CA  E9 ; # small j\n"
                "    CB  EA ; # small k\n"
                "    CC  EB ; # small l\n"
                "    CD  EC ; # small m\n"
                "    CE  ED ; # small n\n"
                "    CF  EE ; # small o\n"
                "\n"
                "    D0  EF ; # small p\n"
                "    D1  FF ; # small ya\n"
                "    D2  F0 ; # small r\n"
                "    D3  F1 ; # small s\n"
                "    D4  F2 ; # small t\n"
                "    D5  F3 ; # small u\n"
                "    D6  E6 ; # small zh\n"
                "    D7  E2 ; # small v\n"
                "    D8  FC ; # small soft sign\n"
                "    D9  FB ; # small y\n"
                "    DA  E7 ; # small z\n"
                "    DB  F8 ; # small sh\n"
                "    DC  FD ; # small e\n"
                "    DD  F9 ; # small shch\n"
                "    DE  F7 ; # small ch\n"
                "    DF  FA ; # small hard sign\n"
                "\n"
                "    E0  DE ; # capital YU\n"
                "    E1  C0 ; # capital A\n"
                "    E2  C1 ; # capital B\n"
                "    E3  D6 ; # capital TS\n"
                "    E4  C4 ; # capital D\n"
                "    E5  C5 ; # capital YE\n"
                "    E6  D4 ; # capital F\n"
                "    E7  C3 ; # capital G\n"
                "    E8  D5 ; # capital KH\n"
                "    E9  C8 ; # capital I\n"
                "    EA  C9 ; # capital J\n"
                "    EB  CA ; # capital K\n"
                "    EC  CB ; # capital L\n"
                "    ED  CC ; # capital M\n"
                "    EE  CD ; # capital N\n"
                "    EF  CE ; # capital O\n"
                "\n"
                "    F0  CF ; # capital P\n"
                "    F1  DF ; # capital YA\n"
                "    F2  D0 ; # capital R\n"
                "    F3  D1 ; # capital S\n"
                "    F4  D2 ; # capital T\n"
                "    F5  D3 ; # capital U\n"
                "    F6  C6 ; # capital ZH\n"
                "    F7  C2 ; # capital V\n"
                "    F8  DC ; # capital soft sign\n"
                "    F9  DB ; # capital Y\n"
                "    FA  C7 ; # capital Z\n"
                "    FB  D8 ; # capital SH\n"
                "    FC  DD ; # capital E\n"
                "    FD  D9 ; # capital SHCH\n"
                "    FE  D7 ; # capital CH\n"
                "    FF  DA ; # capital hard sign\n"
                "}\n");

    // Close the file
    if (fclose(fp) != 0) {
        perror("[Error] While closing conf/koi-win file");
        return;  // Exit function on error
    }

    printf("[File Created] conf/koi-win file created.\n");
}

void mime_types(){
    // Create and open the HTML file
    FILE *fp = fopen("conf/mime.types", "w");
    if (fp == NULL) {
        perror("[Error] While creating conf/mime.types file");
        return;  // Exit function on error
    }

    // Write HTML content to the file
    fprintf(fp, "\n"
                "types {\n"
                "    text/html                                        html htm shtml;\n"
                "    text/css                                         css;\n"
                "    text/xml                                         xml;\n"
                "    image/gif                                        gif;\n"
                "    image/jpeg                                       jpeg jpg;\n"
                "    application/javascript                           js;\n"
                "    application/atom+xml                             atom;\n"
                "    application/rss+xml                              rss;\n"
                "\n"
                "    text/mathml                                      mml;\n"
                "    text/plain                                       txt;\n"
                "    text/vnd.sun.j2me.app-descriptor                 jad;\n"
                "    text/vnd.wap.wml                                 wml;\n"
                "    text/x-component                                 htc;\n"
                "\n"
                "    image/avif                                       avif;\n"
                "    image/png                                        png;\n"
                "    image/svg+xml                                    svg svgz;\n"
                "    image/tiff                                       tif tiff;\n"
                "    image/vnd.wap.wbmp                               wbmp;\n"
                "    image/webp                                       webp;\n"
                "    image/x-icon                                     ico;\n"
                "    image/x-jng                                      jng;\n"
                "    image/x-ms-bmp                                   bmp;\n"
                "\n"
                "    font/woff                                        woff;\n"
                "    font/woff2                                       woff2;\n"
                "\n"
                "    application/java-archive                         jar war ear;\n"
                "    application/json                                 json;\n"
                "    application/mac-binhex40                         hqx;\n"
                "    application/msword                               doc;\n"
                "    application/pdf                                  pdf;\n"
                "    application/postscript                           ps eps ai;\n"
                "    application/rtf                                  rtf;\n"
                "    application/vnd.apple.mpegurl                    m3u8;\n"
                "    application/vnd.google-earth.kml+xml             kml;\n"
                "    application/vnd.google-earth.kmz                 kmz;\n"
                "    application/vnd.ms-excel                         xls;\n"
                "    application/vnd.ms-fontobject                    eot;\n"
                "    application/vnd.ms-powerpoint                    ppt;\n"
                "    application/vnd.oasis.opendocument.graphics      odg;\n"
                "    application/vnd.oasis.opendocument.presentation  odp;\n"
                "    application/vnd.oasis.opendocument.spreadsheet   ods;\n"
                "    application/vnd.oasis.opendocument.text          odt;\n"
                "    application/vnd.openxmlformats-officedocument.presentationml.presentation\n"
                "                                                     pptx;\n"
                "    application/vnd.openxmlformats-officedocument.spreadsheetml.sheet\n"
                "                                                     xlsx;\n"
                "    application/vnd.openxmlformats-officedocument.wordprocessingml.document\n"
                "                                                     docx;\n"
                "    application/vnd.wap.wmlc                         wmlc;\n"
                "    application/wasm                                 wasm;\n"
                "    application/x-7z-compressed                      7z;\n"
                "    application/x-cocoa                              cco;\n"
                "    application/x-java-archive-diff                  jardiff;\n"
                "    application/x-java-jnlp-file                     jnlp;\n"
                "    application/x-makeself                           run;\n"
                "    application/x-perl                               pl pm;\n"
                "    application/x-pilot                              prc pdb;\n"
                "    application/x-rar-compressed                     rar;\n"
                "    application/x-redhat-package-manager             rpm;\n"
                "    application/x-sea                                sea;\n"
                "    application/x-shockwave-flash                    swf;\n"
                "    application/x-stuffit                            sit;\n"
                "    application/x-tcl                                tcl tk;\n"
                "    application/x-x509-ca-cert                       der pem crt;\n"
                "    application/x-xpinstall                          xpi;\n"
                "    application/xhtml+xml                            xhtml;\n"
                "    application/xspf+xml                             xspf;\n"
                "    application/zip                                  zip;\n"
                "\n"
                "    application/octet-stream                         bin exe dll;\n"
                "    application/octet-stream                         deb;\n"
                "    application/octet-stream                         dmg;\n"
                "    application/octet-stream                         iso img;\n"
                "    application/octet-stream                         msi msp msm;\n"
                "\n"
                "    audio/midi                                       mid midi kar;\n"
                "    audio/mpeg                                       mp3;\n"
                "    audio/ogg                                        ogg;\n"
                "    audio/x-m4a                                      m4a;\n"
                "    audio/x-realaudio                                ra;\n"
                "\n"
                "    video/3gpp                                       3gpp 3gp;\n"
                "    video/mp2t                                       ts;\n"
                "    video/mp4                                        mp4;\n"
                "    video/mpeg                                       mpeg mpg;\n"
                "    video/quicktime                                  mov;\n"
                "    video/webm                                       webm;\n"
                "    video/x-flv                                      flv;\n"
                "    video/x-m4v                                      m4v;\n"
                "    video/x-mng                                      mng;\n"
                "    video/x-ms-asf                                   asx asf;\n"
                "    video/x-ms-wmv                                   wmv;\n"
                "    video/x-msvideo                                  avi;\n"
                "}\n");

    // Close the file
    if (fclose(fp) != 0) {
        perror("[Error] While closing conf/mime.types file");
        return;  // Exit function on error
    }

    printf("[File Created] conf/mime.types file created.\n");
}

void nginx_conf(){
    // Create and open the HTML file
    FILE *fp = fopen("conf/nginx.conf", "w");
    if (fp == NULL) {
        perror("[Error] While creating conf/nginx.conf file");
        return;  // Exit function on error
    }

    // Write HTML content to the file
    fprintf(fp, "\n"
                "#user  nobody;\n"
                "worker_processes  1;\n"
                "\n"
                "#error_log  logs/error.log;\n"
                "#error_log  logs/error.log  notice;\n"
                "#error_log  logs/error.log  info;\n"
                "\n"
                "#pid        logs/nginx.pid;\n"
                "\n"
                "\n"
                "events {\n"
                "    worker_connections  1024;\n"
                "}\n"
                "\n"
                "\n"
                "http {\n"
                "    include       mime.types;\n"
                "    default_type  application/octet-stream;\n"
                "\n"
                "    #log_format  main  '$remote_addr - $remote_user [$time_local] \"$request\" '\n"
                "    #                  '$status $body_bytes_sent \"$http_referer\" '\n"
                "    #                  '\"$http_user_agent\" \"$http_x_forwarded_for\"';\n"
                "\n"
                "    #access_log  logs/access.log  main;\n"
                "\n"
                "    sendfile        on;\n"
                "    #tcp_nopush     on;\n"
                "\n"
                "    #keepalive_timeout  0;\n"
                "    keepalive_timeout  65;\n"
                "\n"
                "    #gzip  on;\n"
                "\n"
                "    server {\n"
                "        listen       80;\n"
                "        server_name  localhost;\n"
                "\n"
                "        #charset koi8-r;\n"
                "\n"
                "        #access_log  logs/host.access.log  main;\n"
                "\n"
                "        location / {\n"
                "            root   html;\n"
                "            index  index.html index.htm;\n"
                "        }\n"
                "\n"
                "        #error_page  404              /404.html;\n"
                "\n"
                "        # redirect server error pages to the static page /50x.html\n"
                "        #\n"
                "        error_page   500 502 503 504  /50x.html;\n"
                "        location = /50x.html {\n"
                "            root   html;\n"
                "        }\n"
                "\n"
                "        # proxy the PHP scripts to Apache listening on 127.0.0.1:80\n"
                "        #\n"
                "        #location ~ \\.php$ {\n"
                "        #    proxy_pass   http://127.0.0.1;\n"
                "        #}\n"
                "\n"
                "        # pass the PHP scripts to FastCGI server listening on 127.0.0.1:9000\n"
                "        #\n"
                "        #location ~ \\.php$ {\n"
                "        #    root           html;\n"
                "        #    fastcgi_pass   127.0.0.1:9000;\n"
                "        #    fastcgi_index  index.php;\n"
                "        #    fastcgi_param  SCRIPT_FILENAME  /scripts$fastcgi_script_name;\n"
                "        #    include        fastcgi_params;\n"
                "        #}\n"
                "\n"
                "        # deny access to .htaccess files, if Apache's document root\n"
                "        # concurs with nginx's one\n"
                "        #\n"
                "        #location ~ /\\.ht {\n"
                "        #    deny  all;\n"
                "        #}\n"
                "    }\n"
                "\n"
                "\n"
                "    # another virtual host using mix of IP-, name-, and port-based configuration\n"
                "    #\n"
                "    #server {\n"
                "    #    listen       8000;\n"
                "    #    listen       somename:8080;\n"
                "    #    server_name  somename  alias  another.alias;\n"
                "\n"
                "    #    location / {\n"
                "    #        root   html;\n"
                "    #        index  index.html index.htm;\n"
                "    #    }\n"
                "    #}\n"
                "\n"
                "\n"
                "    # HTTPS server\n"
                "    #\n"
                "    #server {\n"
                "    #    listen       443 ssl;\n"
                "    #    server_name  localhost;\n"
                "\n"
                "    #    ssl_certificate      cert.pem;\n"
                "    #    ssl_certificate_key  cert.key;\n"
                "\n"
                "    #    ssl_session_cache    shared:SSL:1m;\n"
                "    #    ssl_session_timeout  5m;\n"
                "\n"
                "    #    ssl_ciphers  HIGH:!aNULL:!MD5;\n"
                "    #    ssl_prefer_server_ciphers  on;\n"
                "\n"
                "    #    location / {\n"
                "    #        root   html;\n"
                "    #        index  index.html index.htm;\n"
                "    #    }\n"
                "    #}\n"
                "\n"
                "}\n");

    // Close the file
    if (fclose(fp) != 0) {
        perror("[Error] While closing conf/nginx.conf file");
        return;  // Exit function on error
    }

    printf("[File Created] conf/nginx.conf file created.\n");
}

void scgi_params(){
    // Create and open the HTML file
    FILE *fp = fopen("conf/scgi_params", "w");
    if (fp == NULL) {
        perror("[Error] While creating conf/scgi_params file");
        return;  // Exit function on error
    }

    // Write HTML content to the file
    fprintf(fp, "\n"
                "scgi_param  REQUEST_METHOD     $request_method;\n"
                "scgi_param  REQUEST_URI        $request_uri;\n"
                "scgi_param  QUERY_STRING       $query_string;\n"
                "scgi_param  CONTENT_TYPE       $content_type;\n"
                "\n"
                "scgi_param  DOCUMENT_URI       $document_uri;\n"
                "scgi_param  DOCUMENT_ROOT      $document_root;\n"
                "scgi_param  SCGI               1;\n"
                "scgi_param  SERVER_PROTOCOL    $server_protocol;\n"
                "scgi_param  REQUEST_SCHEME     $scheme;\n"
                "scgi_param  HTTPS              $https if_not_empty;\n"
                "\n"
                "scgi_param  REMOTE_ADDR        $remote_addr;\n"
                "scgi_param  REMOTE_PORT        $remote_port;\n"
                "scgi_param  SERVER_PORT        $server_port;\n"
                "scgi_param  SERVER_NAME        $server_name;\n");

    // Close the file
    if (fclose(fp) != 0) {
        perror("[Error] While closing conf/scgi_params file");
        return;  // Exit function on error
    }

    printf("[File Created] conf/scgi_params file created.\n");
}

void uwsgi_params(){
    // Create and open the HTML file
    FILE *fp = fopen("conf/uwsgi_params", "w");
    if (fp == NULL) {
        perror("[Error] While creating conf/uwsgi_params file");
        return;  // Exit function on error
    }

    // Write HTML content to the file
    fprintf(fp, "    \n"
                "uwsgi_param  QUERY_STRING       $query_string;\n"
                "uwsgi_param  REQUEST_METHOD     $request_method;\n"
                "uwsgi_param  CONTENT_TYPE       $content_type;\n"
                "uwsgi_param  CONTENT_LENGTH     $content_length;\n"
                "\n"
                "uwsgi_param  REQUEST_URI        $request_uri;\n"
                "uwsgi_param  PATH_INFO          $document_uri;\n"
                "uwsgi_param  DOCUMENT_ROOT      $document_root;\n"
                "uwsgi_param  SERVER_PROTOCOL    $server_protocol;\n"
                "uwsgi_param  REQUEST_SCHEME     $scheme;\n"
                "uwsgi_param  HTTPS              $https if_not_empty;\n"
                "\n"
                "uwsgi_param  REMOTE_ADDR        $remote_addr;\n"
                "uwsgi_param  REMOTE_PORT        $remote_port;\n"
                "uwsgi_param  SERVER_PORT        $server_port;\n"
                "uwsgi_param  SERVER_NAME        $server_name;\n");

    // Close the file
    if (fclose(fp) != 0) {
        perror("[Error] While closing conf/uwsgi_params file");
        return;  // Exit function on error
    }

    printf("[File Created] conf/uwsgi_params file created.\n");
}

void win_utf(){
    // Create and open the HTML file
    FILE *fp = fopen("conf/win-utf", "w");
    if (fp == NULL) {
        perror("[Error] While creating conf/win-utf file");
        return;  // Exit function on error
    }

    // Write HTML content to the file
    fprintf(fp, "\n"
                "# This map is not a full windows-1251 <> utf8 map: it does not\n"
                "# contain Serbian and Macedonian letters.  If you need a full map,\n"
                "# use contrib/unicode2nginx/win-utf map instead.\n"
                "\n"
                "charset_map  windows-1251  utf-8 {\n"
                "\n"
                "    82  E2809A ; # single low-9 quotation mark\n"
                "\n"
                "    84  E2809E ; # double low-9 quotation mark\n"
                "    85  E280A6 ; # ellipsis\n"
                "    86  E280A0 ; # dagger\n"
                "    87  E280A1 ; # double dagger\n"
                "    88  E282AC ; # euro\n"
                "    89  E280B0 ; # per mille\n"
                "\n"
                "    91  E28098 ; # left single quotation mark\n"
                "    92  E28099 ; # right single quotation mark\n"
                "    93  E2809C ; # left double quotation mark\n"
                "    94  E2809D ; # right double quotation mark\n"
                "    95  E280A2 ; # bullet\n"
                "    96  E28093 ; # en dash\n"
                "    97  E28094 ; # em dash\n"
                "\n"
                "    99  E284A2 ; # trade mark sign\n"
                "\n"
                "    A0  C2A0 ;   # &nbsp;\n"
                "    A1  D18E ;   # capital Byelorussian short U\n"
                "    A2  D19E ;   # small Byelorussian short u\n"
                "\n"
                "    A4  C2A4 ;   # currency sign\n"
                "    A5  D290 ;   # capital Ukrainian soft G\n"
                "    A6  C2A6 ;   # borken bar\n"
                "    A7  C2A7 ;   # section sign\n"
                "    A8  D081 ;   # capital YO\n"
                "    A9  C2A9 ;   # (C)\n"
                "    AA  D084 ;   # capital Ukrainian YE\n"
                "    AB  C2AB ;   # left-pointing double angle quotation mark\n"
                "    AC  C2AC ;   # not sign\n"
                "    AD  C2AD ;   # soft hypen\n"
                "    AE  C2AE ;   # (R)\n"
                "    AF  D087 ;   # capital Ukrainian YI\n"
                "\n"
                "    B0  C2B0 ;   # &deg;\n"
                "    B1  C2B1 ;   # plus-minus sign\n"
                "    B2  D086 ;   # capital Ukrainian I\n"
                "    B3  D196 ;   # small Ukrainian i\n"
                "    B4  D291 ;   # small Ukrainian soft g\n"
                "    B5  C2B5 ;   # micro sign\n"
                "    B6  C2B6 ;   # pilcrow sign\n"
                "    B7  C2B7 ;   # &middot;\n"
                "    B8  D191 ;   # small yo\n"
                "    B9  E28496 ; # numero sign\n"
                "    BA  D194 ;   # small Ukrainian ye\n"
                "    BB  C2BB ;   # right-pointing double angle quotation mark\n"
                "\n"
                "    BF  D197 ;   # small Ukrainian yi\n"
                "\n"
                "    C0  D090 ;   # capital A\n"
                "    C1  D091 ;   # capital B\n"
                "    C2  D092 ;   # capital V\n"
                "    C3  D093 ;   # capital G\n"
                "    C4  D094 ;   # capital D\n"
                "    C5  D095 ;   # capital YE\n"
                "    C6  D096 ;   # capital ZH\n"
                "    C7  D097 ;   # capital Z\n"
                "    C8  D098 ;   # capital I\n"
                "    C9  D099 ;   # capital J\n"
                "    CA  D09A ;   # capital K\n"
                "    CB  D09B ;   # capital L\n"
                "    CC  D09C ;   # capital M\n"
                "    CD  D09D ;   # capital N\n"
                "    CE  D09E ;   # capital O\n"
                "    CF  D09F ;   # capital P\n"
                "\n"
                "    D0  D0A0 ;   # capital R\n"
                "    D1  D0A1 ;   # capital S\n"
                "    D2  D0A2 ;   # capital T\n"
                "    D3  D0A3 ;   # capital U\n"
                "    D4  D0A4 ;   # capital F\n"
                "    D5  D0A5 ;   # capital KH\n"
                "    D6  D0A6 ;   # capital TS\n"
                "    D7  D0A7 ;   # capital CH\n"
                "    D8  D0A8 ;   # capital SH\n"
                "    D9  D0A9 ;   # capital SHCH\n"
                "    DA  D0AA ;   # capital hard sign\n"
                "    DB  D0AB ;   # capital Y\n"
                "    DC  D0AC ;   # capital soft sign\n"
                "    DD  D0AD ;   # capital E\n"
                "    DE  D0AE ;   # capital YU\n"
                "    DF  D0AF ;   # capital YA\n"
                "\n"
                "    E0  D0B0 ;   # small a\n"
                "    E1  D0B1 ;   # small b\n"
                "    E2  D0B2 ;   # small v\n"
                "    E3  D0B3 ;   # small g\n"
                "    E4  D0B4 ;   # small d\n"
                "    E5  D0B5 ;   # small ye\n"
                "    E6  D0B6 ;   # small zh\n"
                "    E7  D0B7 ;   # small z\n"
                "    E8  D0B8 ;   # small i\n"
                "    E9  D0B9 ;   # small j\n"
                "    EA  D0BA ;   # small k\n"
                "    EB  D0BB ;   # small l\n"
                "    EC  D0BC ;   # small m\n"
                "    ED  D0BD ;   # small n\n"
                "    EE  D0BE ;   # small o\n"
                "    EF  D0BF ;   # small p\n"
                "\n"
                "    F0  D180 ;   # small r\n"
                "    F1  D181 ;   # small s\n"
                "    F2  D182 ;   # small t\n"
                "    F3  D183 ;   # small u\n"
                "    F4  D184 ;   # small f\n"
                "    F5  D185 ;   # small kh\n"
                "    F6  D186 ;   # small ts\n"
                "    F7  D187 ;   # small ch\n"
                "    F8  D188 ;   # small sh\n"
                "    F9  D189 ;   # small shch\n"
                "    FA  D18A ;   # small hard sign\n"
                "    FB  D18B ;   # small y\n"
                "    FC  D18C ;   # small soft sign\n"
                "    FD  D18D ;   # small e\n"
                "    FE  D18E ;   # small yu\n"
                "    FF  D18F ;   # small ya\n"
                "}\n");

    // Close the file
    if (fclose(fp) != 0) {
        perror("[Error] While closing conf/win-utf file");
        return;  // Exit function on error
    }

    printf("[File Created] conf/win-utf file created.\n");
}


void create_conf(){
    // Create the directory
    if (system("mkdir conf") == -1) {
        perror("[Error] While creating conf folder");
        return;  // Exit function on error
    }
    printf("[File Created] ./conf folder created.\n");
    fastcgi_params();
    fastcgi_conf();
    koi_utf();
    koi_win();
    mime_types();
    nginx_conf();
    scgi_params();
    uwsgi_params();
    win_utf();
}


// Improved function to create an HTML directory and file
void create_html() {
    // Create the directory
    if (MKDIR("html") == -1 && errno != EEXIST) {
        perror("[Error] While creating html folder");
        return;  // Exit function on error
    }
    printf("[File Created] ./html folder created or already exists.\n");

    // Check if the HTML file already exists
    FILE *fp = fopen("html/index.html", "r");
    if (fp != NULL) {
        fclose(fp);  // Close the file if it exists
        printf("[Info] html/index.html already exists. No new file created.\n");
        return;  // Exit function since file already exists
    }

    // Create and open the HTML file for writing
    fp = fopen("html/index.html", "w");
    if (fp == NULL) {
        perror("[Error] While creating html/index.html file");
        return;  // Exit function on error
    }

    // Write HTML content to the file
    fprintf(fp, "<!DOCTYPE html>\n"
                "<html lang='en'>\n"
                "<head>\n"
                "    <meta charset='UTF-8'>\n"
                "    <meta name='viewport' content='width=device-width, initial-scale=1.0'>\n"
                "    <title>NGinit</title>\n"
                "    <style>\n"
                "        body { margin: 10px; font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; display: flex; flex-direction: column; background-color: #1a1a59; color: wheat; }\n"
                "        h1 { align-self: center; }\n"
                "        p { width: auto; padding: 0 20%; }\n"
                "        a { color: lightblue; }\n"
                "    </style>\n"
                "</head>\n"
                "<body>\n"
                "    <h1>NGinit</h1>\n"
                "    <p>Hey, You have successfully configured your local nginx server, and all files are set. You can now start/continue your development.</p>\n"
                "    <p>{NGinit} Developed by <a href='http://github.com/h4jack/nginit'>@h4jack</a></p>\n"
                "</body>\n"
                "</html>\n");

    // Close the file
    if (fclose(fp) != 0) {
        perror("[Error] While closing html/index.html file");
        return;  // Exit function on error
    }

    printf("[File Created] html/index.html file created.\n");
}


void create_log() {
    // Array of log file paths to create
    const char *files[] = {
        "logs/access.log",
        "logs/error.log"
    };

    // Create the logs directory
    if (MKDIR("logs") != 0) {
        perror("Error creating logs directory");
        return;  // Exit function on error
    }
    printf("[File Created] ./logs folder created.\n");

    // Create log files and handle errors
    for (size_t i = 0; i < sizeof(files) / sizeof(files[0]); ++i) {
        FILE *fp = fopen(files[i], "w");
        if (fp == NULL) {
            perror("Error creating log file");
            return;  // Exit function on error
        }
        fclose(fp);  // Close the file after creation
        printf("[File Created] %s file created.\n", files[i]);
    }
}

void create_temp() {
    // Array of directory paths to create
    const char *directories[] = {
        "temp",
        "temp\\client_body_temp",
        "temp\\fastcgi_temp",
        "temp\\proxy_temp",
        "temp\\scgi_temp",
        "temp\\uwsgi_temp"
    };

    // Number of directories to create
    size_t num_directories = sizeof(directories) / sizeof(directories[0]);

    // Loop through each directory and create it
    for (size_t i = 0; i < num_directories; ++i) {
        if (MKDIR(directories[i]) != 0) {
            // Provide more detailed error information
            printf("[Error] Failed to create directory %s: %s\n", directories[i], strerror(errno));
        } else {
            printf("[File Created] %s folder created.\n", directories[i]);
        }
    }
}


void moveFiles(bool isless){
    if(!isless){
        move_to_html();
        create_conf();
        create_html();
        create_log();
        create_temp();

        printf("\n%d", isless);
    }else{
        printf("This functionality is not available, please try again in new update..\nThank You...");
    }
}

int main(int arglen, char *args[]){
    
    if(arglen < 3){
        if(arglen is 1){
            moveFiles(false);
            return 0;
        }else if(arglen is 2){
            if(not strcmp(args[1], "-h") or not strcmp(args[1], "--help") or not strcmp(args[1], "-v") or not strcmp(args[1], "--version")){
                print_help();
            }else{
                print_error("[ERROR] Wrong Argument Passed...\n");
            }
        }
    }else{
        print_error("[ERROR] Too Many Argument Passed...\n");
    }
    return 0;
}