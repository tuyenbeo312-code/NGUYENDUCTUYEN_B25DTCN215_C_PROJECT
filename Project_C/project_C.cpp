#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<ctype.h>

struct Account {
    char accountId[20];
    char fullName[50];
    char phone[15];
    double balance;
    int status;
};

struct Transaction {
    char transId[20];
    char senderId[20];
    char receiverId[20];
    double amount;
    char type[10];
    char date[20];
};

int isSpace(char *str) {
    if (str == 0 || strlen(str) == 0){
		return 1;
	}
    for (int i = 0; i < strlen(str); i++) {
        if (!isspace(str[i])) {
        	return 0;
		}
    }
    return 1;
}
int isDigits(char *str) {
    if (str == 0 || strlen(str) == 0){
    	return 0;
	} 
    for (int i = 0; i < strlen(str); i++) {
        if (!(str[i] >= '0' && str[i] <= '9')){
        	return 0;
		} 
    }
    return 1;
}
int isDuplicateId(struct Account accounts[], int size, char accountId[]) {
    for (int i = 0; i < size; i++) {
        if (strcmp(accounts[i].accountId, accountId) == 0)
            return 1; 
    }
    return 0; 
}

int isDuplicateName(struct Account accounts[], int size, char *name) {
    for (int i = 0; i < size; i++) {
        if (strcmp(accounts[i].fullName, name) == 0) {
            return 1; 
        }
    }
    return 0; 
}

int isDuplicatePhone(struct Account accounts[], int size, char *phone) {
    for (int i = 0; i < size; i++) {
        if (strcmp(accounts[i].phone, phone) == 0) {
            return 1; 
        }
    }
    return 0; 
}


void newAccount(struct Account accounts[], int *size) {
    char number[20];
    int n;

    printf("Nhap vao so luong tai khoan moi muon them: ");
    fgets(number, sizeof(number), stdin);
    number[strcspn(number, "\n")] = 0;

    if (isSpace(number) || !isDigits(number)) {
        printf("Loi: Vui long nhap lai.\n");
        return;
    }
    n = atoi(number);
    if (n <= 0) {
        printf("Loi: Vui long nhap lai.\n");
        return;
    }
    if (*size + n >= 100) {
        printf("Loi: Mang khong du suc chua.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        struct Account account;
        printf("\n--- Nhap thong tin tai khoan thu %d ---\n", i + 1);

        
        while (1) {
            printf("Nhap ID: ");
            fgets(account.accountId, sizeof(account.accountId), stdin);
            account.accountId[strcspn(account.accountId, "\n")] = 0;

            if (isSpace(account.accountId)) {
                printf("Loi: ID khong duoc de trong.\n");
                continue;
            }
            if (isDuplicateId(accounts, *size, account.accountId)) {
                printf("Loi: ID da ton tai.\n");
                continue;
            }
            if (!isDigits(account.accountId)) {
                printf("Loi: ID khong hop le.\n");
                continue;
            }
            break; 
        }

        
        while (1) {
            printf("Nhap ho va ten: ");
            fgets(account.fullName, sizeof(account.fullName), stdin);
            account.fullName[strcspn(account.fullName, "\n")] = 0;

            if (isSpace(account.fullName)) {
                printf("Loi: Ten khong duoc de trong.\n");
                continue;
            }
			int j, errorName = 0;
            for (j = 0; j < strlen(account.fullName); j++) {
                if (!((account.fullName[j] >= 'a' && account.fullName[j] <= 'z') || (account.fullName[j] >= 'A' && account.fullName[j] <= 'Z') || 
				account.fullName[j] == ' ')) {
                    errorName = 1;
                    break;
                }
            }
			if (errorName == 1){
				printf("Loi: Ten khong hop le.\n");
				continue;
			}
            if(isDuplicateName(accounts, *size, account.fullName)){
            	printf("Loi: Ten da ton tai o tai khoan khac.\n");
            	continue;
			}
            break; 
        }

        while (1) {
            printf("Nhap so dien thoai: ");
            fgets(account.phone, sizeof(account.phone), stdin);
            account.phone[strcspn(account.phone, "\n")] = 0;

            if (strlen(account.phone) != 10 || !isDigits(account.phone)) {
                printf("Loi: So dien thoai khong hop le!!!\n");
                continue;
            }

            if(isDuplicatePhone(accounts, *size, account.phone)){
            	printf("Loi: SDT da ton tai o tai khoan khac.\n");
            	continue;
			}
            break; 
        }

        account.balance = 0;
        account.status = 1;

        accounts[*size] = account;
        (*size)++;
        printf("Tai khoan %s da duoc them thanh cong\n", account.accountId);
    }

    printf("\nDa them %d tai khoan moi. Tong so tai khoan hien tai: %d\n", n, *size);
}

void updateAccount(struct Account accounts[], int size) {
    char accountId[20];
    int i;
    if(size == 0){
        printf("Loi: chua co tai khoan nao de cap nhat!!!\n");
        return;
    }
    printf("Nhap ID tai khoan can cap nhat: ");
    fgets(accountId, sizeof(accountId), stdin);
    accountId[strcspn(accountId, "\n")] = 0;
    if(isSpace(accountId)){
    	printf("Loi: ID khong duoc de trong.\n");
    	return;
	}
	if(!isDigits(accountId)){
		printf("Loi: ID khong hop le.\n");
		return;
	}

    int found = -1;
    for (int i = 0; i < size; i++) {
        if (strcmp(accounts[i].accountId, accountId) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Loi: Khong tim thay tai khoan\n");
        return;
    }
    char newName[50], newPhone[15];
    while (1) {
        printf("Nhap ten moi (de trong neu giu nguyen): ");
        fgets(newName, sizeof(newName), stdin);
        newName[strcspn(newName, "\n")] = 0;

        if (isSpace(newName)) {
            break; 
        }
		int j, validName = 0;
        for (j = 0; j < strlen(newName); j++) {
            if (!((newName[j] >= 'a' && newName[j] <= 'z') || (newName[j] >= 'A' && newName[j] <= 'Z') || newName[j] == ' ')) {
            	validName = 1;
                break;
            }
        }
        if (validName == 1){
        	printf("Loi: Ten moi khong hop le. Chi duoc dung chu cai va khoang trang.\n");
			continue;
		}
        if (isDuplicateName(accounts, size, newName)) {
            if (strcmp(accounts[found].fullName, newName) != 0) {
                printf("Loi: Ten da ton tai o tai khoan khac.\n");
                continue;
            }
        }
        strcpy(accounts[found].fullName, newName);
        break; 
    }

    while (1) {
        printf("Nhap SDT moi (de trong neu giu nguyen): ");
        fgets(newPhone, sizeof(newPhone), stdin);
        newPhone[strcspn(newPhone, "\n")] = 0;

        if (isSpace(newPhone)) {
            break;
        }
        if (strlen(newPhone) != 10 || !isDigits(newPhone)) {
            printf("Loi: SDT khong hop le!!!\n");
            continue; 
        }
        if (isDuplicatePhone(accounts, size, newPhone)) {
            if (strcmp(accounts[found].phone, newPhone) != 0) {
                printf("Loi: SDT da ton tai o tai khoan khac.\n");
                continue;
            }
        }
        strcpy(accounts[found].phone, newPhone);
        break; 
    }
    printf("Cap nhat thanh cong\n");
}


void deleteOrLockAccount(Account accounts[] , int *size ){
	if(*size == 0){
		printf("Loi: Chua co tai khoan nao.\n");
		return;
	}
	char deleteOrLockId[20];
	while(1){
		printf("Nhap vao ID muon khoa hoac xoa: ");
		fgets(deleteOrLockId, sizeof(deleteOrLockId), stdin);
		deleteOrLockId[strcspn(deleteOrLockId, "\n")] = 0;
	
		if (isSpace(deleteOrLockId)) {
        	printf("Loi: ID khong duoc de trong.\n");
        	continue;
    	}
    	if(!isDigits(deleteOrLockId)){
    		printf("Loi: ID khong hop le.\n");
    		continue;
		}
		break;
	}

	int found = -1;
	for(int i = 0; i < *size; i++){
		if(strcmp(accounts[i].accountId, deleteOrLockId) == 0){
			found = i;
			break;
		}
	}
	if(found == -1){
		printf("Loi: Tai khoan khong ton tai!!!\n");
		return;
	}
	printf("________________________________Thong Tin Tai Khoan Hien Tai________________________________\n");
	printf("|Ma tai khoan: %s | Ten tai khoan: %s | So dien thoai: %s | So du: %.2lf | Trang thai: %d | \n", 
	accounts[found].accountId, accounts[found].fullName, accounts[found].phone, accounts[found].balance, accounts[found].status);
	
	while(1){
		printf("Ban muon khoa hay xoa tai khoan? \n");
		printf("1. Khoa tai khoan. \n");
		printf("2. Xoa tai khoan. \n");
		printf("Lua chon cua ban: ");
	
    	char choice[5];
		fgets(choice, sizeof(choice), stdin);
		choice[strcspn(choice, "\n")] = 0;
	
		if (strcmp(choice, "1") == 0) {
        	printf("Ban co chac chan muon KHOA tai khoan nay? (Y/N): ");
        	char confirm[5];
        	fgets(confirm, sizeof(confirm), stdin);
        	confirm[strcspn(confirm, "\n")] = 0;

        	if (strcmp(confirm, "Y") == 0 || strcmp(confirm, "y") == 0) {
           	accounts[found].status = 0;
            	printf("Tai khoan da duoc KHOA thanh cong.\n");
        	} else {
            	printf("Huy thao tac. Tai khoan van giu nguyen trang thai.\n");
        	}

    	} else if (strcmp(choice, "2") == 0) {
        
        	printf("Ban co chac chan muon XOA tai khoan nay? (Y/N): ");
        	char confirm[5];
        	fgets(confirm, sizeof(confirm), stdin);
        	confirm[strcspn(confirm, "\n")] = 0;

        	if (strcmp(confirm, "Y") == 0 || strcmp(confirm, "y") == 0) {
           		for (int i = found; i < *size - 1; i++) {
                	accounts[i] = accounts[i + 1];
            	}
            	(*size)--;
            	printf("Tai khoan da duoc XOA thanh cong.\n");
        	} else {
            	printf("Huy thao tac. Tai khoan van giu nguyen trang thai.\n");
        	}
    	} else {
        	printf("Lua chon khong hop le. Huy thao tac.\n");
        	continue;
    	}
    	break;
	}
}

void searchAccount(struct Account accounts[], int size) {
    if (size == 0) {
        printf("Loi: Chua co tai khoan nao de tim kiem.\n");
        return;
    }

    char keyword[50];

    while (1) {
        printf("Nhap tu khoa tim kiem (ID hoac Ten): ");
        fgets(keyword, sizeof(keyword), stdin);
        keyword[strcspn(keyword, "\n")] = 0;

        if (isSpace(keyword)) {
            printf("Loi: Tu khoa khong duoc de trong.\n");
            continue;
        }
        int isValid = 1;
        for (int i = 0; i < strlen(keyword); i++) {
            char c = keyword[i];
            if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ')) {
                isValid = 0;
                break;
            }
        }
        if (!isValid) {
            printf("Loi: Tu khoa khong duoc chua ky tu dac biet.\n");
            continue;
    	}
        break;
    }

    int found = 0;
    printf("Ket qua tim kiem:\n");
    for (int i = 0; i < size; i++) {
        if (strcmp(accounts[i].accountId, keyword) == 0 ||
            strstr(accounts[i].fullName, keyword) != NULL) {
            printf("|Ma: %s | Ten: %s | SDT: %s | So du: %.2lf | Trang thai: %d |\n",
                   accounts[i].accountId, accounts[i].fullName, accounts[i].phone,
                   accounts[i].balance, accounts[i].status);
            found = 1;
        }
    }

    if (!found) {
        printf("Khong co ket qua phu hop.\n");
    }
}

void printAccount(struct Account accounts[], int size) {
    if (size <= 0) {
        printf("Danh sach trong, moi ban nhap thong tin khach hang vao danh sach\n");
        return;
    }

    char pageStr[10], sizeStr[10];
    int pageNumber, pageSize;

    while (1) {
        printf("Nhap so trang muon in ra: ");
        fgets(pageStr, sizeof(pageStr), stdin);
        pageStr[strcspn(pageStr, "\n")] = 0;

        if (isSpace(pageStr)) {
            printf("Loi: So trang khong duoc de trong.\n");
            continue;
        }
        if (!isDigits(pageStr)) {
            printf("Loi: So trang nhap vao khong hop le.\n");
            continue;
        }
        if (strcmp(pageStr, "0") == 0) {
            printf("Loi: So trang phai lon hon 0.\n");
            continue;
        }
        pageNumber = atoi(pageStr);

        printf("Nhap so luong tai khoan moi trang: ");
        fgets(sizeStr, sizeof(sizeStr), stdin);
        sizeStr[strcspn(sizeStr, "\n")] = 0;

        if (isSpace(sizeStr)) {
            printf("Loi: So luong tai khoan moi trang khong duoc de trong.\n");
            continue;
        }
        if (!isDigits(sizeStr)) {
            printf("Loi: So luong tai khoan moi trang nhap vao khong hop le.\n");
            continue;
        }
        if (strcmp(sizeStr, "0") == 0) {
            printf("Loi: So luong tai khoan moi trang phai lon hon 0.\n");
            continue;
        }
        pageSize = atoi(sizeStr);

        int startIndex = (pageNumber - 1) * pageSize;
        if (startIndex >= size) {
            printf("Khong tim thay du lieu cho trang yeu cau. Vui long nhap lai!\n");
            continue;
        }

        int endIndex = startIndex + pageSize;

        printf("------------------------------------------------TRANG %d------------------------------------------------\n", pageNumber);
        for (int i = startIndex; i < endIndex && i < size; i++) {
            printf("|Ma tai khoan: %s | Ten tai khoan: %s | So dien thoai: %s | So du: %.2lf | Trang thai: %d |\n",
                   accounts[i].accountId, accounts[i].fullName, accounts[i].phone,
                   accounts[i].balance, accounts[i].status);
        }
        break; 
    }
}

void sortByBalance(struct Account accounts[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (accounts[j].balance < accounts[j + 1].balance) {
                struct Account temp = accounts[j];
                accounts[j] = accounts[j + 1];
                accounts[j + 1] = temp;
            }
        }
    }
}

void sortByName(struct Account accounts[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (strcmp(accounts[j].fullName, accounts[j + 1].fullName) > 0) {
                struct Account temp = accounts[j];
                accounts[j] = accounts[j + 1];
                accounts[j + 1] = temp;
            }
        }
    }
}

void sortAccount(struct Account accounts[], int size) {
    if (size == 0) {
        printf("Khong co du lieu can sap xep\n");
        return;
    }

    char choice[10];
    while (1) {
        printf("Chon tieu chi sap xep:\n");
        printf("1. Theo so du giam dan\n");
        printf("2. Theo ten A-Z\n");
        printf("Lua chon cua ban: ");
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = 0;

        if (isSpace(choice) || !isDigits(choice) ) {
            printf("Lua chon khong hop le. Vui long nhap lai.\n");
            continue;
        }

        if (strcmp(choice, "1") == 0) {
            sortByBalance(accounts, size);
            printf("Da sap xep xong theo so du giam dan.\n");
            break;
        } else if (strcmp(choice, "2") == 0) {
            sortByName(accounts, size);
            printf("Da sap xep xong theo ten A-Z.\n");
            break;
        } else {
            printf("Lua chon khong hop le. Vui long nhap lai.\n");
        }
        break;
    }
}

int main() {
    int choice = 0;
    struct Account accounts[100] = {
    	{"01", "Nguyen Van E", "0912345678", 1000.0, 1},
    	{"02", "Nguyen Van B", "0923456789", 500.0, 1},
    	{"03", "Nguyen Van D", "0934567890", 200.0, 1},
    	{"04", "Nguyen Van C", "0945678901", 1200.0, 1},
    	{"05", "Nguyen Van A", "0956789012", 1500.0, 1},
    	{"06", "Nguyen Van G", "0967890123", 900.0, 1},
    	{"07", "Nguyen Van J", "0978901234", 800.0, 1},
    	{"08", "Nguyen Van I", "0989012345", 100.0, 1},
    	{"09", "Nguyen Van H", "0990123456", 600.0, 1},
    	{"10", "Nguyen Van F", "0901234567", 750.0, 1}
	};
	int size = 10;
    char str[20];
    do {
        printf("||===================================MENU=====================================||\n");
        printf("||                          1.Them moi tai khoan.                             ||\n");
        printf("||                          2.Cap nhat thong tin.                             ||\n");
        printf("||                          3.Quan ly trang thai( Khoa / Xoa ).               ||\n");
        printf("||                          4.Tra cuu( Search ).                              ||\n");
        printf("||                          5.Danh sach( Phan trang ).                        ||\n");
        printf("||                          6.Sap xep danh sach.                              ||\n");
        printf("||                          7.Giao dich chuyen khoan.                         ||\n");
        printf("||                          8.Lich su giao dich.                              ||\n");
        printf("||                          9.Thoat                                           ||\n");
        printf("||============================================================================||\n");
        printf("Nhap lua chon cua ban(1 - 9): ");
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = 0;
        if(isSpace(str)){
        	printf("Loi: Lua chon khong duoc de trong.\n");
        	continue;
		}
		if(!isDigits(str)){
			printf("Loi: Lua chon chi duoc nhap chu so.\n");
			continue;
		}
		choice = atoi(str);
		if (choice < 1 || choice > 9) {
    		printf("Loi: Chi duoc chon tu 1 den 9.\n");
    		continue;
		}

        switch (choice) {
            case 1: {
                newAccount(accounts, &size);
                break;
            }
            case 2:{
            	updateAccount(accounts, size);
				break;
			}
            case 3:{
            	deleteOrLockAccount(accounts, &size);
				break;
			}
            case 4:{
            	searchAccount(accounts, size);
				break;
			}
            case 5:{
            	printAccount(accounts, size);
				break;
			}
            case 6:{
            	sortAccount(accounts, size);
				break;
			}
            case 7:
            case 8:
            case 9: {
                printf("Cam on vi da den!!!\n");
                break;
            }
            default: {
                printf("Lua chon khong hop le. Vui long nhap lai.\n");
                break;
            }
        }
    } while (choice != 9);
    return 0;
}
