/*************************************************************************
	> File Name: ls.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年09月22日 星期六 10时06分41秒
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <time.h>
#include <grp.h>
#include <sys/types.h> 
#include <utime.h>

int ls(DIR *dir, int order, const char *c) {
    struct dirent *p;
    while ((p = readdir(dir))!= NULL) {
        if (p->d_name[0] == '.' && order == 1) continue;
        struct stat st;
        char str[1000];
        strcpy(str, c);
        strcat(str, p->d_name);
        stat(str, &st);
        char permission[20] = "----------";
        if (st.st_mode & S_IRUSR) permission[1] = 'r';
        if (st.st_mode & S_IWUSR) permission[2] = 'w';
        if (st.st_mode & S_IXUSR) permission[3] = 'x';
        if (st.st_mode & S_IRGRP) permission[4] = 'r';
        if (st.st_mode & S_IWGRP) permission[5] = 'w';
        if (st.st_mode & S_IXGRP) permission[6] = 'x';
        if (st.st_mode & S_IROTH) permission[7] = 'r';
        if (st.st_mode & S_IWOTH) permission[8] = 'w';
        if (st.st_mode & S_IXOTH) permission[9] = 'x';
        if (st.st_mode & S_IFDIR) permission[0] = 'd';

        struct passwd *user;
        struct group *g;
        user = getpwuid(st.st_uid);
        g = getgrgid(st.st_gid);
        printf("%s %3ld %s %s %5ld ", permission, st.st_nlink, user->pw_name, g->gr_name, st.st_size);
        if (permission[0] == 'd') {
            printf("\e[34;1m%s\e[0m\n", p->d_name);
        } else if (permission[3] == 'x') {
            printf("\e[32;1m%s\e[0m\n", p->d_name);
        } else {
            printf("%s\n", p->d_name);
        }
    }
}

int main(int argc, char **argv) {
    DIR *dir;
    int num = argc;
    dir = opendir(".");
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            dir = opendir(argv[i]);
            printf("\n%s:\n", argv[i]);
            if (argv[i][0] != '-') {
                ls(dir, 1, argv[i]);
            }
        }
    } else {
        ls(dir, 1, "./");
    }
    closedir(dir);
    return 0;
}
