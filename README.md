# Work3 학생 관리 시스템 (Student Management System)

간단한 학생 정보 관리를 위한 C 프로그램입니다.

## 기능

- 학생 정보 입력/조회/수정/삭제
- 이름으로 검색 (정확한 이름 또는 부분 이름)
- 데이터베이스 파일 저장

## 컴파일 및 실행

```bash
# 컴파일
gcc -Wall -o stuManager stuManager.c

# 실행
./stuManager stdinfo.db
```

## Docker 환경에서 실행

```bash
# 이미지 빌드
docker build -t student-manager .

# 실행
docker run -it --rm student-manager
```

## 사용 방법

1. 프로그램 실행 후 메뉴에서 원하는 기능 선택
2. 프롬프트 지시에 따라 학생 정보 입력
3. 파일은 자동으로 저장됨