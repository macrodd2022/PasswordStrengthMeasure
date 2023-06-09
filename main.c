#include <stdio.h>
#include <string.h>

// the acceptable max password length
#define PASSWORD_MAX_LENGTH 20

// the type of a character
// for checking type
#define TYPE_MIXED 9
#define TYPE_NUM 0
#define TYPE_UPR 1
#define TYPE_LWR 2
#define TYPE_MIN_VALUE                                                         \
  { '0', 'a', 'A' }
#define TYPE_MAX_VALUE                                                         \
  { '9', 'z', 'Z' }

// check the length of the password
int password_length_check(char password[]);
// print the order of suggestion and suggestion itself
// we use a function here because the order can be counted easier
void raise_suggestion(int do_raise, char suggestion[], int *order);
// check whether there is repeated character for 3 times and above
int check_repeated_char(char password[]);
// check whether there is repeated words for 2 times and above
int check_repeated_words(char password[]);
// check whether password consists of only numbers or letters
int check_only_one_type(char password[]);
// analyze the type of word (for example, is it all number?)
int analyze_type(char word[]);

int main() {
  // print information
  printf("Welcome to Password Strength Measure!\n\n");
  printf("This program measures your password's strength.\n");
  printf("Your password should not be longer than %d characters.\n\n",
         PASSWORD_MAX_LENGTH);

  // ask for password
  printf("Please type your password to test:\n");

  // the password's variable
  char password[PASSWORD_MAX_LENGTH + 1];

  // read password
  scanf("%s", password);
  printf("\n");

  // check if the password is too long
  if (!password_length_check(password)) {
    printf("Password too long! Please input shorter password!\n");
    return 1;
  }

  // the order of suggestion
  // if it remained being 0 after all checks, that means the password is strong
  // enough.
  int suggestion_order = 0;

  // CHECK 1
  // the length of password
  raise_suggestion(strlen(password) <= 8, "Too short", &suggestion_order);

  // CHECK 2
  // repeated same character
  raise_suggestion(check_repeated_char(password), "Repeated character",
                   &suggestion_order);
  // repeated words
  raise_suggestion(check_repeated_words(password), "Repeated words",
                   &suggestion_order);
  // only number or letter
  raise_suggestion(!(analyze_type(password) == 9), "Only number or letter",
                   &suggestion_order);

  // check wether the password is strong enough
  if (!suggestion_order)
    printf("Great! We can give no suggestion for your strong password!\n");
  else
    printf("\nAbove are our suggestion.\n");

  return 0;
}

int password_length_check(char password[]) {
  int flag = 0; // whether there is a \0 in the variable
  int i = 0;
  while (i < PASSWORD_MAX_LENGTH + 1) {
    if (password[i] == 0) {
      flag = 1;
      break;
    }
    i++;
  }
  return flag;
}

void raise_suggestion(int do_raise, char suggestion[], int *order) {
  if (do_raise) {
    if (!*order) {
      printf("We have some suggestions here:\n\n");
    }
    printf("#%d %s\n", *order + 1, suggestion);
    (*order)++;
  }
}

int check_repeated_char(char password[]) {
  int flag = 0, cnt = 0;
  int i;
  int len = strlen(password);
  char prev = 0;
  for (i = 0; i < len; i++) {
    if (prev == password[i]) {
      cnt++;
    } else {
      cnt = 0;
    }
    if (cnt >= 2) {
      flag = 1;
    }
    prev = password[i];
  }
  return flag;
}

int check_repeated_words(char password[]) {
  int password_len = strlen(password); // length of password
  int max_word_len = password_len / 2; // max length of word to check
  int flag = 0;                        // 1 for ok
  int i, j, m, n;
  // printf("%d %d\n", password_len, max_word_len); // for debug
  // i is the length of word to test
  // j is the start position of getting word sto test
  // m is the start position of getting word to check repeat
  // n is the checking positon
  for (i = 2; i <= max_word_len; i++)
    for (j = 0; j <= password_len - i * 2; j++)
      for (m = i + j; m <= password_len - i; m++) {
        int flag_repeat; // whether there is repeating
        for (n = 0; n < i; n++) {
          flag_repeat = 1;
          // printf("%d %d %d %d\n", i, j, m, n); // for debug
          if (password[j + n] != password[m + n]) {
            flag_repeat = 0;
            break;
          }
        }
        if (flag_repeat) {
          flag = 1;
          return flag;
        }
      }
  return flag;
}

int check_only_one_type(char password[]) { return 0; }

int analyze_type(char word[]) {
  char first = word[0];
  int type;
  int min_value[3] = TYPE_MIN_VALUE, max_value[3] = TYPE_MAX_VALUE;
  if (first >= min_value[TYPE_NUM] && first <= max_value[TYPE_NUM]) {
    type = TYPE_NUM;
  } else if (first >= min_value[TYPE_UPR] && first <= max_value[TYPE_UPR]) {
    type = TYPE_UPR;
  } else if (first >= min_value[TYPE_LWR] && first <= max_value[TYPE_LWR]) {
    type = TYPE_LWR;
  }
  int i;
  for (i = 1; i < strlen(word); i++)
    if (!(word[i] >= min_value[type] && word[i] <= max_value[type])) {
      type = TYPE_MIXED;
      break;
    }
  return type;
}
