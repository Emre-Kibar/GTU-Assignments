int sum(int a, int b);

int sum(int a, int b) {
    return a + b;
}

int main() {
    int x = 10;
    int y = 20;
    int result = sum(x, y);
    
    if (result > 25) {
        printf("Result is greater than 25\n");
        x = 5;
    }

    for (int i = 0; i < 10; i++) {
        printf("%d\n", i);
    }

    while (x < 20) {
        printf("%d\n", x);
        x = x + 1;
    }

    return 0;
}
