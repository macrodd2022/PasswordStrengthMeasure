#include <stdio.h>
#include <string.h>

// the acceptable max password length
#define PASSWORD_MAX_LENGTH 20

// check the length of the password
int password_length_check(char password[]);
// print the order of suggestion and suggestion itself
// we use a function here because the order can be counted easier
void print_suggestion(char suggestion[], int *suggestion_order);

int main() {
  // print information
  printf("Welcome to Password Strength Measure!\n\n");
  printf("This program measures your password's strength.\n");
  printf("Your password should not be longer than %d characters.\n\n", PASSWORD_MAX_LENGTH);

  // ask for password
  printf("Please type your password to test:\n");

  // the password's variable
  char password[PASSWORD_MAX_LENGTH+1];

  // read password
  scanf("%s", password);
  printf("\n");
  
  // check if the password is too long
  if (!password_length_check(password)){
    printf("Password too long! Please input shorter password!\n");
    return 1;
  }

  // the order of suggestion
  // if it remained being 0 after all checks, that means the password is strong enough.
  int suggestion_order = 0;
  
  // CHECK 1
  // the length of password
  if (strlen(password) <= 6)
    print_suggestion("Your password is too short.", &suggestion_order);

  // CHECK 2
  // repeated same character

  // TODO 

  // check wether the password is strong enough
  if (!suggestion_order)
    printf("Great! We can give no suggestion for your strong password!");
  else
    printf("\nAbove are our suggestion.");

  return 0;
}

int password_length_check(char password[]) {
  int flag = 0; // whether there is a \0 in the variable
  int i = 0;
  while(i < PASSWORD_MAX_LENGTH + 1) {
    if(password[i]==0){
      flag = 1;
      break;
    }
    i++;
  }
  return flag;
}

void print_suggestion(char suggestion[], int *order) {
  if (!*order) {
    printf("We have some suggestions here:\n\n");
  }
  printf("#%d %s\n", *order+1, suggestion);
  (*order) ++;
}
