#include <stdio.h>
#include <string.h>

struct UserAccount {
    int user_id;
    char username[50];
    int plan_type;
    int days_overdue;
    int active_devices;
    long final_fee;
};

int main() {
    struct UserAccount users[100];
    int n, i;
    long total_revenue = 0;
    int downgraded_count = 0;
    do {
        printf("Nhap so luong tai khoan (1 - 100): ");
        scanf("%d", &n);
        if (n < 1 || n > 100) {
            printf(" -> Loi: So luong tai khoan khong hop le!\n");
        }
    } while (n < 1 || n > 100);

    for (i = 0; i < n; i++) {
        printf("\n--- Nhap thong tin tai khoan thu %d ---\n", i + 1);
        printf("Ma TK: ");
        scanf("%d", &users[i].user_id);
        
        while (getchar() != '\n'); 
        
        printf("Ten TK: ");
        fgets(users[i].username, sizeof(users[i].username), stdin);
        users[i].username[strcspn(users[i].username, "\n")] = '\0';

        do {
            printf("Loai goi (1=Free, 2=Personal, 3=Family): ");
            scanf("%d", &users[i].plan_type);
            if (users[i].plan_type < 1 || users[i].plan_type > 3) {
                printf(" -> Loi: Loai goi phai nam trong khoang [1, 3]!\n");
            }
        } while (users[i].plan_type < 1 || users[i].plan_type > 3);

        do {
            printf("So ngay no cuoc: ");
            scanf("%d", &users[i].days_overdue);
            if (users[i].days_overdue < 0) {
                printf(" -> Loi: So ngay no khong duoc phep am!\n");
            }
        } while (users[i].days_overdue < 0);

        do {
            printf("So thiet bi dang ket noi: ");
            scanf("%d", &users[i].active_devices);
            if (users[i].active_devices < 0) {
                printf(" -> Loi: So thiet bi khong duoc phep am!\n");
            }
        } while (users[i].active_devices < 0);
    }

    for (i = 0; i < n; i++) {
        if (users[i].plan_type == 1) {
            users[i].final_fee = 0;
        } else if (users[i].plan_type == 2) {
            users[i].final_fee = 120000;
        } else if (users[i].plan_type == 3) {
            users[i].final_fee = 250000;
        }

        if (users[i].days_overdue >= 3) {
            if (users[i].plan_type != 1) {
                downgraded_count++; 
            }
            users[i].plan_type = 1;
            users[i].final_fee = 0;
        }

        if (users[i].plan_type == 2 && users[i].active_devices > 1) {
            long extra_devices = users[i].active_devices - 1;
            users[i].final_fee += (extra_devices * 30000);
        }

        total_revenue += users[i].final_fee;
    }

    printf("\n=================================== BAO CAO HE THONG SAAS ===================================\n");
    printf("%-10s %-20s %-10s %-15s %-15s %-20s\n", "Ma TK", "Ten TK", "Ma Goi", "So Thiet Bi", "So Ngay No", "Phi Thuc Thu (VND)");
    printf("---------------------------------------------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("%-10d %-20s %-10d %-15d %-15d %-20ld\n",
               users[i].user_id,
               users[i].username,
               users[i].plan_type,
               users[i].active_devices,
               users[i].days_overdue,
               users[i].final_fee);
    }
    printf("---------------------------------------------------------------------------------------------\n");
    printf("Tong doanh thu thuc thu: %ld VND\n", total_revenue);
    printf("Tong so tai khoan bi ha cap ve Free: %d\n", downgraded_count);

    return 0;
}