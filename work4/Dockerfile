FROM gcc:latest

WORKDIR /app

# 소스 코드 복사
COPY . .

# 라이브러리 생성 및 컴파일
RUN gcc -c copy.c && \
    ar rc libmylib.a copy.o && \
    ranlib libmylib.a && \
    gcc -Wall -o main main.c -L. -lmylib

# 실행 명령
ENTRYPOINT ["./main"]