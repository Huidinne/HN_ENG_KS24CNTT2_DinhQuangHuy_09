#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    int id;
    char name[50];
    int age;
    char hometown[50];
    char division[50];
    char phone[15];
}Employee;

typedef struct SingleNode{
    Employee employee;
    struct SingleNode* next;
}SingleNode;

typedef struct  DoubleNode {
    Employee employee;
    struct DoubleNode* next;
    struct DoubleNode* prev;
}DoubleNode;
typedef struct {
    SingleNode* current_head;
    DoubleNode* completed_head;
    int next_id;
} EmployeeManager;
EmployeeManager* create_employee_manager(){
    EmployeeManager* manager = (EmployeeManager*)malloc(sizeof(EmployeeManager));
    manager->current_head = NULL;
    manager->completed_head = NULL;
    manager->next_id = 1;
    return manager;
}
void add_employee(EmployeeManager* employee) {
    SingleNode* new_node = (SingleNode*)malloc(sizeof(SingleNode));
    new_node->next = NULL;

    printf("Nhap ten nhan vien: ");
    fflush(stdin);
    fgets(new_node->employee.name, sizeof(new_node->employee.name), stdin);
    new_node->employee.name[strcspn(new_node->employee.name, "\n")] = '\0';

    printf("Nhap tuoi: ");
    scanf("%d", &new_node->employee.age);
    getchar();

    printf("Nhap que quan nhan vien: ");
    fgets(new_node->employee.hometown, sizeof(new_node->employee.hometown), stdin);
    new_node->employee.hometown[strcspn(new_node->employee.hometown, "\n")] = '\0';

    printf("Nhap phong ban truc thuoc: ");
    fgets(new_node->employee.division, sizeof(new_node->employee.division), stdin);
    new_node->employee.division[strcspn(new_node->employee.division, "\n")] = '\0';

    printf("Nhap so dien thoai: ");
    fgets(new_node->employee.phone, sizeof(new_node->employee.phone), stdin);
    new_node->employee.phone[strcspn(new_node->employee.phone, "\n")] = '\0';



    new_node->employee.id = employee->next_id++;
    if (employee->current_head == NULL) {
        employee->current_head = new_node;
    } else {
        SingleNode* temp = employee->current_head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
    printf("Them nhan vien thanh cong!\n");
}

void display_employee(EmployeeManager* employee) {
    SingleNode* current = employee->current_head;
    if (!current) {
        printf("Danh sach hien tai rong.\n");
        return;
    }
    while (current!=NULL) {
        printf("ID: %d\n", current->employee.id);
        printf("Name: %s\n", current->employee.name);
        printf("Age: %d\n", current->employee.age);
        printf("Hometown: %s\n", current->employee.hometown);
        printf("Division: %s\n", current->employee.division);
        printf("Phone: %s\n", current->employee.phone);
        current = current->next;
    }
    DoubleNode* completed = employee->completed_head;
    while (completed!=NULL) {
        printf("ID: %d\n", current->employee.id);
        printf("Name: %s\n", current->employee.name);
        printf("Age: %d\n", current->employee.age);
        printf("Hometown: %s\n", current->employee.hometown);
        printf("Division: %s\n", current->employee.division);
        printf("Phone: %s\n", current->employee.phone);
        completed = completed->next;
    }
}
void delete_employee(EmployeeManager* employee) {
    int id;
    printf("Nhap ID sach can xoa: ");
    scanf("%d", &id);

    SingleNode* current = employee->current_head;
    SingleNode* prev = NULL;

    while (current != NULL) {
        if (current->employee.id == id) {
            if (prev == NULL) {
                employee->current_head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Da xoa nhan vien co ID %d\n", id);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Khong tim thay nhan vien co ID %d\n", id);

}

void update_employee(EmployeeManager* employee) {
    int id;
    printf("Nhap ID sach muon cap nhat: ");
    scanf("%d", &id);
    SingleNode* new_node = employee->current_head;
    while (new_node != NULL && new_node->employee.id != id) {
        new_node = new_node->next;
    }
    if (new_node != NULL) {
        printf("Nhap ten nhan vien: ");
        fflush(stdin);
        fgets(new_node->employee.name, sizeof(new_node->employee.name), stdin);
        new_node->employee.name[strcspn(new_node->employee.name, "\n")] = '\0';

        printf("Nhap tuoi: ");
        scanf("%d", &new_node->employee.age);
        getchar();

        printf("Nhap que quan nhan vien: ");
        fgets(new_node->employee.hometown, sizeof(new_node->employee.hometown), stdin);
        new_node->employee.hometown[strcspn(new_node->employee.hometown, "\n")] = '\0';

        printf("Nhap phong ban truc thuoc: ");
        fgets(new_node->employee.division, sizeof(new_node->employee.division), stdin);
        new_node->employee.division[strcspn(new_node->employee.division, "\n")] = '\0';

        printf("Nhap so dien thoai: ");
        fgets(new_node->employee.phone, sizeof(new_node->employee.phone), stdin);
        new_node->employee.phone[strcspn(new_node->employee.phone, "\n")] = '\0';
    }else {
        printf("Khong tim thay nhan vien\n");
    }
}

void mark_retired(EmployeeManager* employee) {
    int id;
    printf("Nhap ID nhan vien nghi viec: ");
    scanf("%d", &id);

    SingleNode* current = employee->current_head;
    SingleNode* prev = NULL;

    while (current != NULL && current->employee.id != id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Khong tim nhan vien co ID %d trong danh sach.\n", id);
        return;
    }

    if (prev == NULL) {
        employee->current_head = current->next;
    } else {
        prev->next = current->next;
    }

    DoubleNode* new_node = (DoubleNode*)malloc(sizeof(DoubleNode));
    new_node->employee = current->employee;
    new_node->next = employee->completed_head;
    new_node->prev = NULL;
    if (employee->completed_head != NULL)
        employee->completed_head->prev = new_node;
    employee->completed_head = new_node;

    free(current);
    printf("Da danh dau nhan vien co ID %d la da nghi viec.\n", id);
}

void sort_employee(EmployeeManager* employee) {

}

void to_lower(char* str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') str[i] += 32;
    }
}

void search_employee(EmployeeManager* employee) {
    char keyword[100];
    char title_lower[100], keyword_lower[100];
    getchar();
    printf("Nhap ten nhan vien can tim: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = 0;

    strcpy(keyword_lower, keyword);
    to_lower(keyword_lower);

    int found = 0;
    SingleNode* current = employee->current_head;
    while (current) {
        strcpy(title_lower, current->employee.name);
        to_lower(title_lower);
        if (strstr(title_lower, keyword_lower)) {
            printf("ID: %d\n", current->employee.id);
            printf("Name: %s\n", current->employee.name);
            printf("Age: %d\n", current->employee.age);
            printf("Hometown: %s\n", current->employee.hometown);
            printf("Division: %s\n", current->employee.division);
            printf("Phone: %s\n", current->employee.phone);
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("Khong tim thay nhan vien nao co tu khoa \"%s\".\n", keyword);
    }
}

void free_employee(EmployeeManager* employee) {
    SingleNode* current = employee->current_head;
    while (current) {
        SingleNode* tmp = current;
        current = current->next;
        free(tmp);
    }
    DoubleNode* done = employee->completed_head;
    while (done) {
        DoubleNode* tmp = done;
        done = done->next;
        free(tmp);
    }
    free(employee);
}

 int main() {
     EmployeeManager* manager = create_employee_manager();
     int choice;

     do {
         printf("\n=== EMPLOYEE MANAGER ===\n");
         printf("1. Them nhan vien\n");
         printf("2. Hien thi danh sach tat ca nhan vien\n");
         printf("3. Xoa nhan vien\n");
         printf("4. Cap nhat thong tin mot nhan vien\n");
         printf("5. Danh dau nhan vien nghi viec\n");
         printf("6. Sap xep nhan vien theo phong ban\n");
         printf("7. Tim kiem nhan vien\n");
         printf("8. Thoat\n");
         printf("Nhap lua chon: ");
         scanf("%d", &choice);

         switch (choice) {
             case 1: add_employee(manager); break;
             case 2: display_employee(manager); break;
             case 3: delete_employee(manager); break;
             case 4: update_employee(manager); break;
             case 5: mark_retired(manager); break;
             case 6: sort_employee(manager); break;
             case 7: search_employee(manager); break;
             case 8: printf("Thoat chuong trinh.\n"); break;
             default: printf("Lua chon khong hop le!\n");
         }
     } while (choice != 8);
     free_employee(manager);
     return 0;
}