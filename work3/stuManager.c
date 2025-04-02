// stuManager.c
#include "student.h"

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void displayMenu() {
    printf("\n<학생파일관리프로그램>\n");
    printf("1. 학생 정보 입력\n");
    printf("2. 모든 학생정보 리스트로 보기\n");
    printf("3. 학생 정보 검색(이름으로 검색)\n");
    printf("4. 학생 정보 검색(2자이상입력검색 가능)\n");
    printf("5. 학생 정보 갱신\n");
    printf("6. 학생 정보 삭제\n");
    printf("0. 종료\n");
    printf("입력: ");
}

void addStudent(FILE *fp) {
    struct student s;
    
    printf("\n<학생정보입력>\n");
    printf("ID: ");
    scanf("%d", &s.id);
    clearInputBuffer();
    
    printf("이름: ");
    fgets(s.name, MAX_NAME_LEN, stdin);
    s.name[strcspn(s.name, "\n")] = 0;
    
    printf("주소: ");
    fgets(s.address, MAX_ADDR_LEN, stdin);
    s.address[strcspn(s.address, "\n")] = 0;
    
    printf("전화번호: ");
    fgets(s.phone, MAX_PHONE_LEN, stdin);
    s.phone[strcspn(s.phone, "\n")] = 0;
    
    printf("생년: ");
    scanf("%d", &s.birth_year);
    clearInputBuffer();
    
    fseek(fp, 0, SEEK_END);
    fwrite(&s, sizeof(struct student), 1, fp);
    printf("학생 정보가 저장되었습니다.\n");
}

void displayAllStudents(FILE *fp) {
    struct student s;
    
    printf("\n<학생정보목록>\n");
    printf("%-5s %-20s %-50s %-20s %-4s\n", "ID", "이름", "주소", "전화번호", "생년");
    printf("-------------------------------------------------------------------------\n");
    
    fseek(fp, 0, SEEK_SET);
    while (fread(&s, sizeof(struct student), 1, fp) == 1) {
        printf("%-5d %-20s %-50s %-20s %-4d\n", s.id, s.name, s.address, s.phone, s.birth_year);
    }
}

void searchByExactName(FILE *fp) {
    struct student s;
    char name[MAX_NAME_LEN];
    int found = 0;
    
    printf("\n<학생정보검색(이름)>\n");
    printf("검색할 이름: ");
    fgets(name, MAX_NAME_LEN, stdin);
    name[strcspn(name, "\n")] = 0;
    
    printf("\n<검색결과>\n");
    printf("%-5s %-20s %-50s %-20s %-4s\n", "ID", "이름", "주소", "전화번호", "생년");
    printf("-------------------------------------------------------------------------\n");
    
    fseek(fp, 0, SEEK_SET);
    while (fread(&s, sizeof(struct student), 1, fp) == 1) {
        if (strcmp(s.name, name) == 0) {
            printf("%-5d %-20s %-50s %-20s %-4d\n", s.id, s.name, s.address, s.phone, s.birth_year);
            found = 1;
        }
    }
    
    if (!found) {
        printf("해당 이름의 학생을 찾을 수 없습니다.\n");
    }
}

void searchByPartialName(FILE *fp) {
    struct student s;
    char name[MAX_NAME_LEN];
    int found = 0;
    
    printf("\n<학생정보검색(부분일치)>\n");
    printf("검색할 이름(2자 이상): ");
    fgets(name, MAX_NAME_LEN, stdin);
    name[strcspn(name, "\n")] = 0;
    
    if (strlen(name) < 2) {
        printf("검색어는 2자 이상이어야 합니다.\n");
        return;
    }
    
    printf("\n<검색결과>\n");
    printf("%-5s %-20s %-50s %-20s %-4s\n", "ID", "이름", "주소", "전화번호", "생년");
    printf("-------------------------------------------------------------------------\n");
    
    fseek(fp, 0, SEEK_SET);
    while (fread(&s, sizeof(struct student), 1, fp) == 1) {
        if (strstr(s.name, name) != NULL) {
            printf("%-5d %-20s %-50s %-20s %-4d\n", s.id, s.name, s.address, s.phone, s.birth_year);
            found = 1;
        }
    }
    
    if (!found) {
        printf("검색 조건에 맞는 학생을 찾을 수 없습니다.\n");
    }
}

void updateStudent(FILE *fp) {
    struct student s;
    int id, found = 0;
    long pos;
    
    printf("\n<학생정보갱신>\n");
    printf("갱신할 학생 ID: ");
    scanf("%d", &id);
    clearInputBuffer();
    
    fseek(fp, 0, SEEK_SET);
    while (fread(&s, sizeof(struct student), 1, fp) == 1) {
        if (s.id == id) {
            pos = ftell(fp) - sizeof(struct student);
            printf("\n<현재정보>\n");
            printf("ID: %d\n", s.id);
            printf("이름: %s\n", s.name);
            printf("주소: %s\n", s.address);
            printf("전화번호: %s\n", s.phone);
            printf("생년: %d\n", s.birth_year);
            
            printf("\n<새로운정보입력>\n");
            printf("이름: ");
            fgets(s.name, MAX_NAME_LEN, stdin);
            s.name[strcspn(s.name, "\n")] = 0;
            
            printf("주소: ");
            fgets(s.address, MAX_ADDR_LEN, stdin);
            s.address[strcspn(s.address, "\n")] = 0;
            
            printf("전화번호: ");
            fgets(s.phone, MAX_PHONE_LEN, stdin);
            s.phone[strcspn(s.phone, "\n")] = 0;
            
            printf("생년: ");
            scanf("%d", &s.birth_year);
            clearInputBuffer();
            
            fseek(fp, pos, SEEK_SET);
            fwrite(&s, sizeof(struct student), 1, fp);
            printf("학생 정보가 갱신되었습니다.\n");
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("해당 ID의 학생을 찾을 수 없습니다.\n");
    }
}

void deleteStudent(FILE *fp) {
    struct student s;
    int id, found = 0;
    FILE *temp;
    char tempFileName[] = "temp.db";
    
    printf("\n<학생정보삭제>\n");
    printf("삭제할 학생 ID: ");
    scanf("%d", &id);
    clearInputBuffer();
    
    temp = fopen(tempFileName, "wb");
    if (!temp) {
        printf("임시 파일을 생성할 수 없습니다.\n");
        return;
    }
    
    fseek(fp, 0, SEEK_SET);
    while (fread(&s, sizeof(struct student), 1, fp) == 1) {
        if (s.id != id) {
            fwrite(&s, sizeof(struct student), 1, temp);
        } else {
            found = 1;
        }
    }
    
    fclose(temp);
    
    if (found) {
        fclose(fp);
        remove("stdinfo.db");
        rename(tempFileName, "stdinfo.db");
        printf("학생 정보가 삭제되었습니다.\n");
        fp = fopen("stdinfo.db", "rb+");
        if (!fp) {
            fprintf(stderr, "파일을 다시 열 수 없습니다.\n");
            exit(1);
        }
    } else {
        remove(tempFileName);
        printf("해당 ID의 학생을 찾을 수 없습니다.\n");
    }
}

int main(int argc, char *argv[]) {
    FILE *fp;
    int choice;
    
    if (argc != 2 || strcmp(argv[1], "stdinfo.db") != 0) {
        fprintf(stderr, "사용법: %s stdinfo.db\n", argv[0]);
        return 1;
    }
    
    // 파일이 없으면 새로 생성
    fp = fopen(argv[1], "rb+");
    if (!fp) {
        fp = fopen(argv[1], "wb+");
        if (!fp) {
            fprintf(stderr, "파일을 열 수 없습니다.\n");
            return 1;
        }
    }
    
    while (1) {
        displayMenu();
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                addStudent(fp);
                break;
            case 2:
                displayAllStudents(fp);
                break;
            case 3:
                searchByExactName(fp);
                break;
            case 4:
                searchByPartialName(fp);
                break;
            case 5:
                updateStudent(fp);
                break;
            case 6:
                deleteStudent(fp);
                break;
            case 0:
                printf("프로그램을 종료합니다.\n");
                fclose(fp);
                return 0;
            default:
                printf("잘못된 선택입니다. 다시 시도하세요.\n");
        }
    }
    
    return 0;
}