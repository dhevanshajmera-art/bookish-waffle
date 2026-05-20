#include <stdio.h>

#include <stdlib.h>

#include <time.h>


#define MAX_LOG 500
char log_name[MAX_LOG][56];
int log_price[MAX_LOG];
int log_qty[MAX_LOG];
int log_count = 0;

void add_to_log(const char * name, int price, int qty) {

    for (int i = 0; i < log_count; i++) {
        int j = 0;
        while (name[j] && log_name[i][j] == name[j]) j++;
        if (!name[j] && !log_name[i][j] && log_price[i] == price) {
            log_qty[i] += qty;
            return;
        }
    }
    if (log_count < MAX_LOG) {
        int j = 0;
        while (name[j]) {
            log_name[log_count][j] = name[j];
            j++;
        }
        log_name[log_count][j] = '\0';
        log_price[log_count] = price;
        log_qty[log_count] = qty;
        log_count++;
    }
}


void print_bill(int table_no, int * bill_no_ptr, float total,
    float discount, int ac) {
    int lucky, guess;
    srand(time(NULL));
    lucky = (rand() % 5) + 1;

    printf("\nLUCKY NUMBER GAME\n");
    printf("Guess a number between 1 and 5: ");
    scanf("%d", & guess);
    if (guess == lucky) {
        printf("Congratulations! You won 10%% discount!\n");
        discount = total * 0.10;
    } else {
        printf("Sorry! Lucky number was %d. No discount.\n", lucky);
    }

    float subtotal = total - discount;
    float gst = subtotal * 0.05;
    float final_total = subtotal + gst;

    printf("\n=======================================================\n");
    printf("================== NEEMSI RESTAURANT ==================\n");
    printf("=======================================================\n");

    time_t t;
    putenv("TZ=IST-5:30");
    tzset();
    t = time(NULL);
    struct tm * tm_info = localtime( & t);
    printf("          Date: %02d-%02d-%d    Time: %02d:%02d:%02d\n",
        tm_info -> tm_mday, tm_info -> tm_mon + 1, tm_info -> tm_year + 1900,
        tm_info -> tm_hour, tm_info -> tm_min, tm_info -> tm_sec);
    printf("          Bill No : %d       Table No: %d\n", ( * bill_no_ptr) ++, table_no);
    if (ac) printf("                    ** AC Section **\n");
    printf("=======================================================\n");
    printf("%-24s %-6s %-9s %-8s\n", "     Item", "Qty", "Price", "    Total");
    printf("-------------------------------------------------------\n");

    for (int i = 0; i < log_count; i++)
        if (log_qty[i] > 0)
            printf("     %-20s %-5d Rs.%-8d   Rs.%-8d\n",
                log_name[i], log_qty[i], log_price[i],
                log_qty[i] * log_price[i]);

    printf("-------------------------------------------------------\n");
    printf("     Subtotal:                               Rs %.2f\n", total);
    printf("     Discount:                               Rs %.2f\n", discount);
    printf("     GST (5%%):                               Rs %.2f\n", gst);
    printf("-------------------------------------------------------\n");
    printf("     FINAL AMOUNT:                           Rs %.2f\n", final_total);
    printf("-------------------------------------------------------\n");
    printf("                THANK YOU! VISIT AGAIN !\n");
    printf("=======================================================\n");
}


float order_items(const char names[][56],
    const int price[], int count) {
    char more;
    int item, quantity;
    float round_total = 0;
    do {
        printf("\nEnter item number: ");
        scanf("%d", & item);
        if (item < 1 || item > count) {
            printf("Invalid item!\n");
            continue;
        }
        printf("Enter quantity: ");
        scanf("%d", & quantity);
        add_to_log(names[item - 1], price[item - 1], quantity);
        round_total += price[item - 1] * quantity;
        printf("Add more items? (y/n): ");
        scanf(" %c", & more);
    } while (more == 'y' || more == 'Y');
    return round_total;
}

float order_items40(const char names[][40],
    const int price[], int count) {
    char more;
    int item, quantity;
    float round_total = 0;
    do {
        printf("\nEnter item number: ");
        scanf("%d", & item);
        if (item < 1 || item > count) {
            printf("Invalid item!\n");
            continue;
        }
        printf("Enter quantity: ");
        scanf("%d", & quantity);
        /* cast to [56] compatible buffer via add_to_log */
        char tmp[56];
        int k = 0;
        while (names[item - 1][k] && k < 55) {
            tmp[k] = names[item - 1][k];
            k++;
        }
        tmp[k] = '\0';
        add_to_log(tmp, price[item - 1], quantity);
        round_total += price[item - 1] * quantity;
        printf("Add more items? (y/n): ");
        scanf(" %c", & more);
    } while (more == 'y' || more == 'Y');
    return round_total;
}

int main() {
    char table;
    int table_no;
    static int bill_no = 101;

    printf("Welcome to the Neemsi Restaurant!\n");
    printf("AC or NON-AC ? (A/N): \n");
    scanf(" %c", & table);
    printf("Enter Table Number: ");
    scanf("%d", & table_no);

    if (table != 'A' && table != 'a' &&
        table != 'N' && table != 'n') {
        printf("Sorry! You have entered an invalid option.\n");
        return 0;
    }

    int ac = (table == 'A' || table == 'a');

    float total = 0;
    float discount = 0;
    char re;

    do {
        int menu;
        printf("\n1. Breakfast Menu\n");
        printf("2. Lunch & Dinner Menu\n");
        printf("3. Around-The-Clock Menu\n");
        printf("Enter choice: ");
        scanf("%d", & menu);

        if (menu == 1) {
            int breakfast;
            printf("\nBREAKFAST MENU (8:00 AM - 12:00 PM)\n");
            printf("1. South Indian\n");
            printf("2. North Indian\n");
            printf("3. Gujarati\n");
            scanf("%d", & breakfast);

            if (breakfast == 1) {
                char items[14][56] = {
                    "Sada Dosa",
                    "Masala Dosa",
                    "Mysore Sada Dosa",
                    "Mysore Masala Dosa",
                    "Open Masala Dosa",
                    "Idli Sambar",
                    "Medu Vada Sambar",
                    "Idli-Vada Sambar",
                    "Podi Idli",
                    "Uttapam",
                    "Onion Uttapam",
                    "Cheese Uttapam",
                    "Extra Butter",
                    "Extra Ghee"
                };
                int price[14] = {
                    80,
                    100,
                    100,
                    120,
                    150,
                    80,
                    100,
                    100,
                    120,
                    80,
                    100,
                    120,
                    20,
                    20
                };
                if (ac)
                    for (int i = 0; i < 14; i++) price[i] += 100;
                printf("\nSOUTH INDIAN MENU\n");
                for (int i = 0; i < 14; i++) printf("%d. %s - Rs %d\n", i + 1, items[i], price[i]);
                total += order_items(items, price, 14);
            }
            else if (breakfast == 2) {
                char items[13][56] = {
                    "Poha",
                    "Upma",
                    "Poori Bhaji",
                    "Chole Bhature",
                    "Aloo Paratha",
                    "Gobi Paratha",
                    "Paneer Paratha",
                    "Stuffed Paratha",
                    "Kachori",
                    "Dahi",
                    "Pickle",
                    "Raita",
                    "Chutney"
                };
                int price[13] = {
                    60,
                    60,
                    80,
                    100,
                    80,
                    80,
                    80,
                    120,
                    60,
                    20,
                    20,
                    20,
                    20
                };
                if (ac)
                    for (int i = 0; i < 13; i++) price[i] += 100;
                printf("\nNORTH INDIAN MENU\n");
                for (int i = 0; i < 13; i++) printf("%d. %s - Rs %d\n", i + 1, items[i], price[i]);
                total += order_items(items, price, 13);
            }
            else if (breakfast == 3) {
                char items[13][56] = {
                    "Dhokla",
                    "Khaman Dhokla",
                    "Methi Thepla",
                    "Khandvi",
                    "Muthiya",
                    "Handvo",
                    "Fafda Jalebi",
                    "Panki",
                    "Paneer Chilla",
                    "Thalipith",
                    "Puranpoli",
                    "Patra",
                    "Sukhdi"
                };
                int price[13] = {
                    80,
                    100,
                    80,
                    80,
                    80,
                    80,
                    120,
                    100,
                    100,
                    100,
                    120,
                    80,
                    120
                };
                if (ac)
                    for (int i = 0; i < 13; i++) price[i] += 100;
                printf("\nGUJARATI MENU\n");
                for (int i = 0; i < 13; i++) printf("%d. %s - Rs %d\n", i + 1, items[i], price[i]);
                total += order_items(items, price, 13);
            }
            else printf("Sorry! You have entered an invalid option.\n");
        }

        else if (menu == 2) {
            int choice;
            printf("\nLUNCH & DINNER MENU (1:00PM - 10:00PM)\n");
            printf("1. Soups & Salads\n");
            printf("2. Starters\n");
            printf("3. Main Course\n");
            printf("4. Rice & Noodles\n");
            printf("5. Beverages\n");
            printf("6. Desserts\n");
            scanf("%d", & choice);

            if (choice == 1) {
                char items[7][40] = {
                    "Clear Soup",
                    "Tomato Soup",
                    "Sweet-Corn Soup",
                    "Veg Manchow Soup",
                    "Cucumber Salad",
                    "Onion Salad",
                    "Tomato Salad"
                };
                int price[7] = {
                    100,
                    120,
                    150,
                    180,
                    60,
                    60,
                    80
                };
                if (ac)
                    for (int i = 0; i < 7; i++) price[i] += 100;
                printf("\nSOUPS & SALADS\n");
                for (int i = 0; i < 7; i++) printf("%d. %s - Rs %d\n", i + 1, items[i], price[i]);
                total += order_items40(items, price, 7);
            }
            else if (choice == 2) {
                char items[50][40] = {
                    "Veg Spring Roll",
                    "Paneer Spring Roll",
                    "Veg Crispy Roll",
                    "Hara Bhara Kebab",
                    "Veg Seekh Kebab",
                    "Paneer Tikka",
                    "Veg Momos (Steam)",
                    "Paneer Momos",
                    "Chilli Paneer (Dry)",
                    "Gobi Manchurian (Dry)",
                    "Veg Cutlet",
                    "Aloo Tikki",
                    "Cheese Aloo Tikki",
                    "Veg Pizza Bites",
                    "Cheese Corn Balls",
                    "Paneer 65",
                    "Veg 65",
                    "Chilli Potato",
                    "Tandoori Aloo",
                    "Tandoori Mushroom",
                    "Veg Pakora",
                    "Paneer Pakora",
                    "Corn Cheese Nuggets",
                    "Paneer Cheese Shots",
                    "Tandoori Paneer Momos",
                    "Paneer Popcorn",
                    "Mushroom Popcorn",
                    "Paneer Nuggets",
                    "Veg Cheese Nuggets",
                    "Paneer Stuffed Tikki",
                    "Veg Kathi Roll",
                    "Paneer Kathi Roll",
                    "Cheese Kathi Roll",
                    "Paneer Tikka Roll",
                    "Veg Manchurian Roll",
                    "Paneer Manchurian Roll",
                    "Corn Popcorn Spicy",
                    "Paneer Stuffed Roll",
                    "Mushroom Stuffed Roll",
                    "Corn Stuffed Roll",
                    "Veg Lollipop Masala",
                    "Paneer Lollipop Masala",
                    "Mushroom Lollipop",
                    "Veg Lollipop Spicy",
                    "Paneer Lollipop Spicy",
                    "Veg Crispy Nuggets",
                    "Veg Crispy Fingers",
                    "Paneer Crispy Fingers",
                    "Mushroom Crispy Fingers",
                    "Cheese Crispy Fingers"
                };
                int price[50] = {
                    100,
                    120,
                    110,
                    130,
                    130,
                    180,
                    110,
                    140,
                    160,
                    150,
                    90,
                    80,
                    100,
                    110,
                    100,
                    150,
                    140,
                    120,
                    130,
                    130,
                    90,
                    120,
                    110,
                    120,
                    140,
                    130,
                    120,
                    110,
                    120,
                    130,
                    140,
                    150,
                    160,
                    150,
                    150,
                    160,
                    120,
                    130,
                    130,
                    130,
                    140,
                    120,
                    120,
                    120,
                    130,
                    130,
                    110,
                    100,
                    100,
                    100
                };
                if (ac)
                    for (int i = 0; i < 50; i++) price[i] += 100;
                printf("\nSTARTERS MENU\n");
                for (int i = 0; i < 50; i++) printf("%d. %s - Rs %d\n", i + 1, items[i], price[i]);
                total += order_items40(items, price, 50);
            }
            else if (choice == 3) {
                char items[25][40] = {
                    "Paneer Butter Masala",
                    "Paneer Tikka Masala",
                    "Shahi Paneer",
                    "Kadai Paneer",
                    "Matar Paneer",
                    "Palak Paneer",
                    "Paneer Bhurji",
                    "Veg Kolhapuri",
                    "Veg Handi",
                    "Veg Makhanwala",
                    "Mix Veg",
                    "Aloo Mutter",
                    "Aloo Palak",
                    "Jeera Aloo",
                    "Dum Aloo",
                    "Chole Masala",
                    "Rajma Masala",
                    "Dal Fry",
                    "Dal Tadka",
                    "Dal Makhani",
                    "Malai Kofta",
                    "Veg Kofta Curry",
                    "Bhindi Masala",
                    "Baingan Bharta",
                    "Veg Jaipuri"
                };
                int price[25] = {
                    260,
                    270,
                    260,
                    250,
                    240,
                    240,
                    230,
                    220,
                    230,
                    240,
                    210,
                    200,
                    200,
                    190,
                    210,
                    220,
                    220,
                    180,
                    190,
                    220,
                    260,
                    240,
                    210,
                    200,
                    230
                };
                if (ac)
                    for (int i = 0; i < 25; i++) price[i] += 100;
                printf("\nMAIN COURSE\n");
                for (int i = 0; i < 25; i++) printf("%d. %s - Rs %d\n", i + 1, items[i], price[i]);
                total += order_items40(items, price, 25);
            }
            else if (choice == 4) {
                char items[25][40] = {
                    "Veg Fried Rice",
                    "Paneer Fried Rice",
                    "Mushroom Fried Rice",
                    "Schezwan Fried Rice",
                    "Jeera Rice",
                    "Lemon Rice",
                    "Steam Rice",
                    "Burnt Garlic Rice",
                    "Hong Kong Rice",
                    "Triple Schezwan Rice",
                    "Veg Hakka Noodles",
                    "Schezwan Noodles",
                    "Paneer Noodles",
                    "Mushroom Noodles",
                    "Garlic Noodles",
                    "Chilli Garlic Noodles",
                    "Singapore Noodles",
                    "Burnt Garlic Noodles",
                    "Veg Chowmein",
                    "Veg American Chopsuey",
                    "Veg Chinese Bhel",
                    "Veg Manchurian Rice",
                    "Veg Manchurian Noodles",
                    "Veg Thai Rice",
                    "Veg Thai Noodles"
                };
                int price[25] = {
                    180,
                    210,
                    200,
                    220,
                    160,
                    170,
                    120,
                    220,
                    240,
                    260,
                    180,
                    220,
                    210,
                    200,
                    190,
                    210,
                    240,
                    220,
                    180,
                    250,
                    160,
                    230,
                    230,
                    240,
                    240
                };
                if (ac)
                    for (int i = 0; i < 25; i++) price[i] += 100;
                printf("\nRICE & NOODLES\n");
                for (int i = 0; i < 25; i++) printf("%d. %s - Rs %d\n", i + 1, items[i], price[i]);
                total += order_items40(items, price, 25);
            }
            else if (choice == 5) {
                char items[25][40] = {
                    "Tea",
                    "Coffee",
                    "Hot Chocolate",
                    "Green Tea",
                    "Masala Tea",
                    "Lemon Tea",
                    "Cold Coffee",
                    "Cold Coffee with Ice Cream",
                    "Chocolate Milkshake",
                    "Strawberry Milkshake",
                    "Vanilla Milkshake",
                    "Mango Milkshake",
                    "Oreo Milkshake",
                    "Fresh Lime Soda",
                    "Sweet Lime Juice",
                    "Orange Juice",
                    "Watermelon Juice",
                    "Pineapple Juice",
                    "Mixed Fruit Juice",
                    "Iced Tea",
                    "Mojito",
                    "Blue Lagoon",
                    "Chocolate Shake",
                    "Buttermilk",
                    "Mineral Water"
                };
                int price[25] = {
                    40,
                    50,
                    70,
                    60,
                    50,
                    60,
                    90,
                    120,
                    130,
                    130,
                    120,
                    140,
                    150,
                    80,
                    100,
                    100,
                    90,
                    110,
                    120,
                    90,
                    110,
                    130,
                    140,
                    60,
                    30
                };
                if (ac)
                    for (int i = 0; i < 25; i++) price[i] += 100;
                printf("\nBEVERAGES\n");
                for (int i = 0; i < 25; i++) printf("%d. %s - Rs %d\n", i + 1, items[i], price[i]);
                total += order_items40(items, price, 25);
            }
            else if (choice == 6) {
                char items[25][40] = {
                    "Gulab Jamun",
                    "Rasgulla",
                    "Rasmalai",
                    "Kaju Katli",
                    "Gajar Halwa",
                    "Moong Dal Halwa",
                    "Vanilla Ice Cream",
                    "Chocolate Ice Cream",
                    "Strawberry Ice Cream",
                    "Butter Scotch Ice Cream",
                    "Chocolate Brownie",
                    "Brownie with Ice Cream",
                    "Chocolate Pastry",
                    "Black Forest Pastry",
                    "Pineapple Pastry",
                    "Chocolate Cake",
                    "Cheesecake",
                    "Fruit Salad with Ice Cream",
                    "Falooda",
                    "Kulfi",
                    "Malai Kulfi",
                    "Rabdi",
                    "Shrikhand",
                    "Jalebi",
                    "Jalebi with Rabdi"
                };
                int price[25] = {
                    90,
                    90,
                    120,
                    150,
                    130,
                    150,
                    80,
                    90,
                    90,
                    100,
                    140,
                    180,
                    120,
                    130,
                    120,
                    150,
                    180,
                    140,
                    160,
                    100,
                    120,
                    140,
                    130,
                    80,
                    130
                };
                if (ac)
                    for (int i = 0; i < 25; i++) price[i] += 100;
                printf("\nDESSERTS\n");
                for (int i = 0; i < 25; i++) printf("%d. %s - Rs %d\n", i + 1, items[i], price[i]);
                total += order_items40(items, price, 25);
            }
            else printf("Sorry! You have entered an invalid option.\n");
        }

        else if (menu == 3) {
            int choice;
            printf("\nAROUND-THE-CLOCK MENU (8:00 AM - 10:00 PM)\n");
            printf("1. Sandwiches\n");
            printf("2. Chaat Items\n");
            printf("3. Upwas Items\n");
            scanf("%d", & choice);

            if (choice == 1) {
                char items[20][40] = {
                    "Plain Veg Sandwich",
                    "Grilled Veg Sandwich",
                    "Cheese Sandwich",
                    "Grilled Cheese Sandwich",
                    "Veg Club Sandwich",
                    "Cheese Veg Grilled Sandwich",
                    "Paneer Sandwich",
                    "Grilled Paneer Sandwich",
                    "Mushroom Sandwich",
                    "Grilled Mushroom Sandwich",
                    "Corn Cheese Sandwich",
                    "Grilled Corn Cheese Sandwich",
                    "Veg Mayo Sandwich",
                    "Veg Toast Sandwich",
                    "Cheese Toast Sandwich",
                    "Coleslaw Sandwich",
                    "Spinach Corn Sandwich",
                    "Chocolate Sandwich",
                    "Veg Cheese Club Sandwich",
                    "Tandoori Paneer Sandwich"
                };
                int price[20] = {
                    80,
                    120,
                    100,
                    130,
                    150,
                    160,
                    140,
                    170,
                    140,
                    170,
                    150,
                    180,
                    120,
                    110,
                    130,
                    140,
                    150,
                    130,
                    180,
                    190
                };
                if (ac)
                    for (int i = 0; i < 20; i++) price[i] += 100;
                printf("\nSANDWICHES\n");
                for (int i = 0; i < 20; i++) printf("%d. %s - Rs %d\n", i + 1, items[i], price[i]);
                total += order_items40(items, price, 20);
            }
            else if (choice == 2) {
                char items[20][40] = {
                    "Pani Puri",
                    "Sev Puri",
                    "Dahi Puri",
                    "Bhel Puri",
                    "Ragda Pattice",
                    "Aloo Tikki Chaat",
                    "Samosa Chaat",
                    "Papdi Chaat",
                    "Dahi Papdi Chaat",
                    "Pav Bhaji",
                    "Masala Pav",
                    "Vada Pav",
                    "Dabeli",
                    "Cheese Dabeli",
                    "Cheese Vada Pav",
                    "Corn Chaat",
                    "Sprouts Chaat",
                    "Chana Chaat",
                    "Fruit Chaat",
                    "Cheese Pav Bhaji"
                };
                int price[20] = {
                    60,
                    80,
                    90,
                    70,
                    100,
                    90,
                    90,
                    90,
                    100,
                    120,
                    90,
                    60,
                    70,
                    90,
                    90,
                    80,
                    90,
                    80,
                    90,
                    150
                };
                if (ac)
                    for (int i = 0; i < 20; i++) price[i] += 100;
                printf("\nCHAAT ITEMS\n");
                for (int i = 0; i < 20; i++) printf("%d. %s - Rs %d\n", i + 1, items[i], price[i]);
                total += order_items40(items, price, 20);
            }
            else if (choice == 3) {
                char items[20][40] = {
                    "Sabudana Khichdi",
                    "Sabudana Vada",
                    "Farali Pattice",
                    "Farali Cutlet",
                    "Farali Chevdo",
                    "Potato Wafers (Farali)",
                    "Upwas Batata Bhaji",
                    "Rajgira Bhakri",
                    "Rajgira Puri",
                    "Singhara Atta Puri",
                    "Singhara Atta Dosa",
                    "Farali Dosa",
                    "Farali Idli",
                    "Curd",
                    "Peanut Ladoo (Farali)",
                    "Coconut Ladoo",
                    "Banana",
                    "Apple",
                    "Sweet Potato Chaat",
                    "Farali Thali"
                };
                int price[20] = {
                    120,
                    130,
                    140,
                    130,
                    110,
                    100,
                    120,
                    80,
                    90,
                    100,
                    130,
                    140,
                    130,
                    60,
                    80,
                    90,
                    40,
                    60,
                    110,
                    180
                };
                if (ac)
                    for (int i = 0; i < 20; i++) price[i] += 100;
                printf("\nUPWAS ITEMS\n");
                for (int i = 0; i < 20; i++) printf("%d. %s - Rs %d\n", i + 1, items[i], price[i]);
                total += order_items40(items, price, 20);
            }
            else printf("Sorry! You have entered an invalid option.\n");
        }
        else {
            printf("Sorry! You have entered an invalid option.\n");
        }

        printf("\nOrder from main menu again? (y/n): ");
        scanf(" %c", & re);

    } while (re == 'y' || re == 'Y');


    print_bill(table_no, & bill_no, total, discount, ac);

    return 0;
}
