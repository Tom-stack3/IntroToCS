'''
Name: Tommy Zaft
Assignment: exercise 7
'''

import sys

'''
* Function Name: read_and_init_store
* Input: path - to read the store from.
* Output: store - a dictionary where the store from the file is saved in.
* Function Operation: we read file where the store is in. we go line by line:
*                   we delete the spaces in the beginning and the end of each line,
*                   if the line is empty we skip it,
*                   else, we save the category and its products, and add it to the store dictionary.
*                   in the end, we return the store dictionary.
'''


def read_and_init_store(path):
    f = open(path, "r")
    store = dict()
    for line in f:
        # we delete the spaces in the beginning and the end of each line
        line = line.strip()
        # if the line is empty
        if not line:
            continue
        category_name, products = line.split(":")
        # we delete the spaces in the beginning
        category_name = category_name.lstrip()
        products = products.split(";")
        products_dict = dict()
        for product in products:
            # if the product is empty
            if not product:
                continue
            product_name, product_price = product.split(",")
            # we delete the spaces in the beginning
            product_price = product_price.lstrip()
            product_name = product_name.lstrip()
            # we add the new product to the products dict
            products_dict[product_name] = product_price
        # we add the category to the store dict
        store[category_name] = products_dict
    f.close()
    return store


'''
* Function Name: print_menu
* Input: none
* Output: none
* Function Operation: prints the menu
'''


def print_menu():
    print("""Please select an operation:
\t0. Exit.
\t1. Query by category.
\t2. Query by item.
\t3. Purchase an item.
\t4. Admin panel.""")


'''
* Function Name: print_admin_menu
* Input: none
* Output: none
* Function Operation: prints the admin menu
'''


def print_admin_menu():
    print("""Admin panel:
\t0. Return to main menu.
\t1. Insert or update an item.
\t2. Save.""")


'''
* Function Name: cache_output
* Input: cached - the cache
*       user_input - the input received from the user.
*       output - the output about to print
* Output: none
* Function Operation: we cache the output under the input and print the output.
'''


def cache_output(cached, user_input, output):
    # we cache the output under the input given
    cached[user_input] = output
    # we print the output
    print(output)


'''
* Function Name: search_and_print_by_category
* Input: store - the store, cached - the cache,
*       first_category - the first category the user entered.
*       second_category - the second category the user entered.
*       input_to_cache - the input to cache.
*       operand - the operand the user chose (we already checked if it's valid): '&', '^' or '|'
* Output: none
* Function Operation: we checked in query_by_category() that the command is valid, so we do the search here.
*                   we save the products of each category in two sets,
*                   then given by the operand we create the print_set, the set to print,
*                   we do it with the sets of the two categories products.
*                   then we cast the print_set to a list, sort it and save it to print_list.
*                   and we call cache_output(), with the print_list as the output.
'''


def search_and_print_by_category(store, cached, first_category, second_category, input_to_cache, operand):
    # we save the product from both categories in sets
    first_products_set = set(product for product in store[first_category])
    second_products_set = set(product for product in store[second_category])
    print_set = set()
    # if we need to find the intersection
    if operand == '&':
        print_set = first_products_set.intersection(second_products_set)
    # if we need to find the union
    elif operand == '|':
        print_set = first_products_set.union(second_products_set)
    # if we need to find the XOR
    elif operand == '^':
        print_set = first_products_set.symmetric_difference(
            second_products_set)
    # we sort the set and save it in a list
    print_list = sorted(list(print_set))
    # we cache the user input with the output and print it. we send the list to print.
    cache_output(cached, input_to_cache, print_list)


'''
* Function Name: query_by_category
* Input: store - the store, cached - the cache.
* Output: none
* Function Operation: we get input from the user for a query by category.
*                   we check if the input has enough data.
*                   (if not we, we call cache_output() with the error message, and exit)
*                   then check if both categories in the input exist in the store
*                   (if not we, we call cache_output() with the error message, and exit)
*                   then we check if the operand entered is valid ('&', '^' or '|')
*                   (if not we, we call cache_output() with the error message, and exit)
*                   if there was no error with the input,
*                   we search and print the query by calling search_and_print_by_category().
'''


def query_by_category(cached, store):
    VALID_NUM_OF_DATA_PARTS = 3
    user_input = input()
    # we strip the spaces from the beginning of each part of the input
    input_split = [split.lstrip() for split in user_input.split(
        ',', VALID_NUM_OF_DATA_PARTS - 1)]
    # after we cleaned the input parts from spaces, we join together with ','
    user_input_cleaned = ','.join(input_split)
    # if the input is already cached
    if user_input_cleaned in cached:
        print("Cached:", cached[user_input_cleaned])
        return
    if len(input_split) < VALID_NUM_OF_DATA_PARTS:
        # we cache the user input with the right error and print it
        cache_output(cached, user_input_cleaned, "Error: not enough data.")
        return
    # we save the second option that could be, putting the categories in a different order.
    input_second_option = ','.join(
        [input_split[1], input_split[0], input_split[2]])
    # if the second option when categories in other order is cached
    if input_second_option in cached:
        print("Cached:", cached[input_second_option])
        return
    error = 'no'
    first_category, second_category, operand = input_split
    # if one of the categories are not in the store
    if first_category not in store or second_category not in store:
        error = "Error: one of the categories does not exist."
    # if the operand entered is not supported
    elif operand not in ['&', '|', '^']:
        error = "Error: unsupported query operation."
    # if there was an error with the output
    if error != 'no':
        # we cache the user input with the right error and print it
        cache_output(cached, user_input_cleaned, error)
    else:
        # we search and print the query.
        search_and_print_by_category(
            store, cached, first_category, second_category, user_input_cleaned, operand)


'''
* Function Name: query_by_product
* Input: store - the store, cached - the cache.
* Output: none
* Function Operation: we get input from the user for a query by product.
*                   we go over the store categories. if the product is in a category,
*                   we add the products in the category (excluding the product entered) to products_set.
*                   after we are done going over the categories,
*                   if didnt find the product the user entered in the store:
*                       we call cache_output() with the error message: "Error: no such item exists."
*                   else:
*                       we cast products_set to a list, sort it and save it to print_list.
*                       then we call cache_output(), with the print_list as the output.
'''


def query_by_product(cached, store):
    user_input = input()
    user_input = user_input.lstrip()
    if user_input in cached:
        print("Cached:", cached[user_input])
        return
    products_set = set()
    found_product = False
    for category in store:
        # if the product the user entered in the category
        if user_input in store[category]:
            found_product = True
            # we go over all the products in the category.
            for product in store[category]:
                # if the product is not the one entered
                if product != user_input:
                    # we add it to the products_set
                    products_set.add(product)
    # if didn't find the product the user entered in the store
    if not found_product:
        cache_output(cached, user_input, "Error: no such item exists.")
    else:
        print_list = sorted(list(products_set))
        cache_output(cached, user_input, print_list)


'''
* Function Name: buy_product
* Input: store - the store, cached - the cache.
* Output: none
* Function Operation: we get input from the user for a product to buy.
*                   we go over the store categories. if the product is in a category,
*                   we save his price in product_price and delete the product from the category.
*                   after we are done going over the categories,
*                   if didnt find the product the user entered in the store:
*                       we call cache_output() with the error message: "Error: no such item exists."
*                   else:
*                       we print that we bought the product with its name and price.
*                       then we clear the cache because the store was changed.
'''


def buy_product(cached, store):
    user_input = input()
    user_input = user_input.lstrip()
    found_product = False
    for category in store:
        # if the product the user entered in the category
        if user_input in store[category]:
            found_product = True
            # we save the price of the product
            product_price = store[category][user_input]
            # we delete the product from the category
            del store[category][user_input]
    # if didn't find the product the user entered in the store
    if not found_product:
        cache_output(cached, user_input, "Error: no such item exists.")
    else:
        output = 'You bought a brand new "' + user_input + \
            '" for ' + str(product_price) + "$."
        print(output)
        # we clear the cache because the store has changed
        cached.clear()


'''
* Function Name: find_right_pass
* Input: admin_path - the path of the file where the password is stored.
* Output: the password from the admin file
* Function Operation: we read the password from the admin file,
*                   delete the new line at the end of the line, if exists. and return it.
'''


def find_right_pass(admin_path):
    f = open(admin_path, "r")
    # the password is in the first line of the file
    password = f.readline()
    # we delete the new line at the end of the line, if exists.
    password = password.rstrip("\n")
    f.close()
    return password


'''
* Function Name: add_product
* Input: store - the store.
* Output: none.
* Function Operation: we get info from the admin about the product to add,
*                   if there is not enough data, or if one of the categories doesn't exists,
*                   or if the price of the product is not positive integer. we print an error and exit.
*                   else, we add the product to the store to the categories entered.
'''


def add_product(store):
    VALID_NUM_OF_DATA_PARTS = 2
    user_input = input()
    user_input = user_input.lstrip()
    input_split = user_input.split(':', VALID_NUM_OF_DATA_PARTS - 1)
    # if there is not enough data
    if len(input_split) < VALID_NUM_OF_DATA_PARTS:
        print("Error: not enough data.")
        return None
    categories = input_split[0].split(',')
    # we clean the spaces before the categories name
    categories = [category.lstrip() for category in categories]
    name_and_price = input_split[1].split(',', VALID_NUM_OF_DATA_PARTS - 1)
    # if there are less than 1 category or not the valid amount (2) in the second part.
    if len(categories) < 1 or len(name_and_price) < VALID_NUM_OF_DATA_PARTS:
        print("Error: not enough data.")
        return None
    for category in categories:
        if category not in store:
            print("Error: one of the categories does not exist.")
            return None
    # we clean the spaces before the name and the price
    product, price = name_and_price[0].lstrip(), name_and_price[1].lstrip()
    # if price not an int or a non negative int
    if not price.isdigit() or int(price) <= 0:
        print("Error: price is not a positive integer.")
        return None
    # if we got here, everything was ok, so we add the product to the store.
    for category in categories:
        store[category][product] = price
    print('Item', '"' + product + '"', 'added.')


'''
* Function Name: save_store
* Input: store - the store, out_path - the path of the file to save the store.
* Output: none.
* Function Operation: we save the categories and the products in it in the out_path,
*                   sorted by alphabetical order.
'''


def save_store(store, out_path):
    f = open(out_path, "w")
    # first we sort the store categories
    categories_sorted = sorted(store)
    for category in categories_sorted:
        line = category + ":"
        # now we sort the products
        products_sorted = sorted(store[category])
        for product in products_sorted:
            line += ' ' + product + ", " + store[category][product] + ";"
        line += "\n"
        f.write(line)
    # we print that we saved the store to the out_path.
    print('Store saved to "', out_path, '".', sep='')
    f.close()


'''
* Function Name: handle_admin
* Input: right_pass - the right admin pass, cached - the cache, store - the store,
*       out_path - the path of the file to save the store.
* Output: none.
* Function Operation: we ask the user for the admin pass. if wrong we return to the main menu.
*                   if the password is right, we enter the admin menu.
*                   we print the admin menu, get the option chosen by the user and call the right function.
*                   we do it in a loop until the user enteres 0.
*                   '0' - we exit the admin menu.
*                   '1' - we call add_product() to add a product, and clear the cache.
*                   '2' - we save the store in the file in out_path
*                   else, we print an error message, "Error: unrecognized operation".
'''


def handle_admin(right_pass, cached, store, out_path):
    pass_entered = input("Password: ")
    # if the user entered a wrong password
    if pass_entered != right_pass:
        print("Error: incorrect password, returning to main menu.")
        # we exit the function back to the main menu.
        return None
    print_admin_menu()
    option = input()
    while option != '0':
        if option == '0':
            # we return to the main menu
            return None
        elif option == '1':
            add_product(store)
            # we clear the cache because the store has changed
            cached.clear()
        elif option == '2':
            save_store(store, out_path)
        else:
            print("Error: unrecognized operation.")
        print_admin_menu()
        option = input()


'''
* Function Name: menu
* Input: store - the store, admin_path - the path of the file where the password is stored.
*       out_path - the path of the file to save the store.
* Output: none.
* Function Operation: we print the menu for the first time, get input from the user and create the cache.
*                   after we get the option chosen by the user we call the right function.
*                   we do it in a loop until the user enteres 0:
*                   print menu, get input and call the right function:
*                   '0' - we exit the menu.
*                   '1' - we call query_by_category() to search by category.
*                   '2' - we call query_by_product() to search by product.
*                   '3' - we call buy_product() to buy a product.
*                   '4' - we get the right admin pass by calling find_right_pass(),
*                       and then call handle_admin().
*                   else, we print an error message, "Error: unrecognized operation".
'''


def menu(store, admin_path, out_path):
    # we print the menu for the first time
    print_menu()
    # we get the input from the user for the first time
    option = input()
    # we create the cache
    cached = dict()
    while option != '0':
        if option == '0':
            return None
        elif option == '1':
            query_by_category(cached, store)
        elif option == '2':
            query_by_product(cached, store)
        elif option == '3':
            buy_product(cached, store)
        elif option == '4':
            right_pass = find_right_pass(admin_path)
            handle_admin(right_pass, cached, store, out_path)
        else:
            print("Error: unrecognized operation.")
        # we print the menu
        print_menu()
        # we get the input from the user
        option = input()


'''
* Function Name: main
* Input: none
* Output: none
* Function Operation: we read and save the parameters sent to the program:
*                   path_to_read - the path of the file where the store is stored.
*                   admin_path - the path of the file where the password is stored.
*                   out_path - the path of the file to save the store.
*                   we save the store in a dictionary by calling read_and_init_store().
*                   then we call menu to handle the interaction with the user.
'''


def main():
    INDEX_OF_FIRST_FILE = 1
    # we save the path to read the store from.
    path_to_read = sys.argv[INDEX_OF_FIRST_FILE]
    # we save the path to read the admin password from.
    admin_path = sys.argv[INDEX_OF_FIRST_FILE + 1]
    # we save the path to save the store in.
    out_path = sys.argv[INDEX_OF_FIRST_FILE + 2]
    # we save the store that is in path_to_read to dictionary named "store"
    store = read_and_init_store(path_to_read)
    menu(store, admin_path, out_path)


if __name__ == "__main__":
    main()
