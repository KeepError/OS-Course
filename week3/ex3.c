#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct Directory Directory;
typedef struct File File;

struct File {
    int id;
    char *name;
    int size;
    char *data;
    Directory * directory;
};

struct Directory {
    File *files[256];
    Directory *directories[256];
    int nf;
    int nd;
    char* path;
};

void add_to_file(File *file, const char * content);
void append_to_file(File *file, const char * content);
void pwd_file(File * file);


void add_file(File* file, Directory *dir);
void add_dir(Directory *dir1, Directory *dir2);

void show_dir(Directory *dir);
void show_file(File *file);
void show_file_detailed(File *file);


int main(void) {
    char content1[] = "int printf(const char * format, ...);";
    char content2[] = "int main(){printf('Hello World');}";
    char content3[] = "//This is a comment in C language";
    char content4[] = "Bourne Again Shell!";
    
    
    Directory home, bin, root;
    home.nd = 0; home.nf = 0; home.path = "/home";
    bin.nd = 0; bin.nf = 0; bin.path = "/bin";
    root.nd = 0; root.nf = 0; root.path = "/";
    
    add_dir(&home, &root);
    add_dir(&bin, &root);
    
    File bash, ex31, ex32;
    bash.id=1; bash.name = "bash";
    ex31.id=2; ex31.name = "ex3_1.c";
    ex32.id=3; ex32.name = "ex3_2.c";
    
    add_file(&bash, &bin);
    add_file(&ex31, &home);
    add_file(&ex32, &home);

    add_to_file(&ex31, content1);
    add_to_file(&ex32, content3);
    add_to_file(&bash, content4);
    
    
    append_to_file(&ex31, content2);

    show_dir(&root);
    show_file_detailed(&bash);
    show_file_detailed(&ex31);
    show_file_detailed(&ex32);

    pwd_file(&bash);
    pwd_file(&ex31);
    pwd_file(&ex32);

    return EXIT_SUCCESS;
}


void show_dir(Directory *dir){
    printf("\nDIRECTORY\n");
    printf(" path: %s\n", dir->path);
    printf(" files:\n");
    printf("    [ ");
    for (int i = 0; i < dir->nf; i++){
        show_file(dir->files[i]);
    }
    printf("]\n");
    printf(" directories:\n");
    printf("    { ");
    
    for (int i = 0; i < dir->nd; i++){
        show_dir(dir->directories[i]);
    }
    printf("}\n");
}

void show_file(File *file){
    printf("%s ", file->name);
}

void show_file_detailed(File *file){
    printf("\nFILE\n");
    printf(" id: %d\n", file->id);
    printf(" name: %s\n", file->name);
    printf(" size: %lu\n", file->size);
    printf(" data:\n");
    printf("    [ %s ]\n", file->data);
}

void add_to_file(File* file, const char* str) {
    char *buffer = malloc(strlen(str));
    strcpy(buffer, str);
    file->data = buffer;
    file->size = strlen(buffer);
}

void append_to_file(File* file, const char* str) {
    char *buffer = malloc(strlen(file->data)+strlen(str));
    strcat(buffer, file->data);
    strcat(buffer, str);
    file->data = buffer;
    file->size = strlen(buffer);
}

void pwd_file(File* file) {
    printf("%s/%s\n", file->directory->path, file->name);
}


void add_file(File* file, Directory* dir) {
    dir->files[dir->nf] = file;
    dir->nf += 1;
    file->directory=dir;
}

void add_dir(Directory *dir1, Directory *dir2){
	if (dir1 && dir2){
		dir2->directories[dir2->nd] = dir1;
		dir2->nd++;
	}
}
