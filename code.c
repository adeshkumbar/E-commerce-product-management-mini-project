#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Product{
int id,quantity;
char name[50];
float price;
struct Product* next;
}Product;
typedef struct Queue{
Product* product;
struct Queue* next;
}Queue;
void addProduct(Product** head);
void displayProducts(Product* head);
void searchProduct(Product* head);
void deleteProduct(Product** head);
void enqueueOrder(Queue** front,Queue** rear,Product* product);
void dequeueOrder(Queue** front,Queue** rear);
void printQueue(Queue* front);
int main(){
Product* productList=NULL;
Queue* orderQueueFront=NULL;
Queue* orderQueueRear=NULL;
int choice;
while(1){
printf("\nE-Commerce Product Management\n");
printf("1. Add Product\n");

printf("2. Display All Products\n");
printf("3. Search Product\n");
printf("4. Delete Product\n");
printf("5. Add to Order Queue\n");
printf("6. Process Order (Dequeue)\n");
printf("7. View Order Queue\n");
printf("8. Exit\n");
printf("Enter your choice: ");
scanf("%d",&choice);
switch(choice){
case 1:addProduct(&productList);break;
case 2:displayProducts(productList);break;
case 3:searchProduct(productList);break;
case 4:deleteProduct(&productList);break;
case 5:if(productList){
enqueueOrder(&orderQueueFront,&orderQueueRear,productList);
printf("Product added to order queue.\n");
}else{
printf("No products available.\n");
}break;
case 6:dequeueOrder(&orderQueueFront,&orderQueueRear);break;
case 7:printQueue(orderQueueFront);break;
case 8:printf("Exiting program...\n");return 0;
default:printf("Invalid choice. Please try again.\n");
}
}return 0;
}
void addProduct(Product** head){
Product* newProduct=(Product*)malloc(sizeof(Product));
if(!newProduct){
printf("Memory allocation failed.\n");
return;
}

printf("Enter product ID: ");
scanf("%d",&newProduct->id);
getchar();
printf("Enter product name: ");
fgets(newProduct->name,sizeof(newProduct->name),stdin);
newProduct->name[strcspn(newProduct->name,"\n")]='\0';
printf("Enter product price: ");
scanf("%f",&newProduct->price);
printf("Enter product quantity: ");
scanf("%d",&newProduct->quantity);
newProduct->next=*head;
*head=newProduct;
printf("Product added successfully.\n");
}
void displayProducts(Product* head){
if (head==NULL){
printf("No products available.\n");
return;
}
printf("\nProduct List:\nID\tName\t\tPrice\tQuantity\n");
printf(" \n");
while (head!=NULL){
printf("%d\t%s\t%.2f\t%d\n",head->id,head->name,head->price,head->quantity);
head=head->next;
}
}
void searchProduct(Product* head){
int id, found=0;
printf("Enter product ID to search: ");
scanf("%d",&id);
while (head!=NULL){
if (head->id==id){
printf("Product found: ID: %d, Name: %s, Price: %.2f, Quantity: %d\n",head-

>id,head->name,head->price,head->quantity);
found=1;break;
}
head=head->next;
}
if (!found){
printf("Product with ID %d not found.\n",id);
}
}
void deleteProduct(Product** head){
int id;
printf("Enter product ID to delete: ");
scanf("%d",&id);
Product *temp=*head,*prev=NULL;
if (temp!=NULL && temp->id==id) {
*head=temp->next;
free(temp);
printf("Product deleted successfully.\n");return;
}
while (temp!=NULL && temp->id!=id){
prev=temp;
temp=temp->next;
}
if (temp==NULL){
printf("Product not found.\n");return;
}
prev->next=temp->next;
free(temp);
printf("Product deleted successfully.\n");
}
void enqueueOrder(Queue** front,Queue** rear,Product* product){
Queue* newOrder=(Queue*)malloc(sizeof(Queue));
newOrder->product=product;

newOrder->next=NULL;
if(*rear==NULL){
*front=*rear=newOrder;
}else{
(*rear)->next=newOrder;
*rear=newOrder;
}
}
void dequeueOrder(Queue** front,Queue** rear){
if (*front==NULL){
printf("Order queue is empty.\n");return;
}
Queue* temp=*front;
*front=(*front)->next;
if (*front==NULL){
*rear=NULL;
}
free(temp);
printf("Order processed.\n");
}
void printQueue(Queue* front){
if (front==NULL){
printf("Order queue is empty.\n");return;
}
printf("\nOrder Queue:\n");
while (front!=NULL){
printf("Product ID: %d, Name: %s\n",front->product->id,front->product->name);
front=front->next;
}
}
