CODE: 

# Merge Sort function to sort orders by delivery time
def merge_sort(orders):
    if len(orders) > 1:
        mid = len(orders) // 2
        left_half = orders[:mid]
        right_half = orders[mid:]

        # Recursively sort both halves
        merge_sort(left_half)
        merge_sort(right_half)

        i = j = k = 0

        # Merge the sorted halves
        while i < len(left_half) and j < len(right_half):
            if left_half[i]['delivery_time'] <= right_half[j]['delivery_time']:
                orders[k] = left_half[i]
                i += 1
            else:
                orders[k] = right_half[j]
                j += 1
            k += 1

        # Copy remaining elements from left_half
        while i < len(left_half):
            orders[k] = left_half[i]
            i += 1
            k += 1

        # Copy remaining elements from right_half
        while j < len(right_half):
            orders[k] = right_half[j]
            j += 1
            k += 1

# Main program
if __name__ == "__main__":
    online_orders = []

    n = int(input("Enter the number of online orders: "))

    for i in range(n):
        order_id = input(f"Enter order ID for order {i+1}: ")
        delivery_time = int(input(f"Enter estimated delivery time (in minutes) for order {i+1}: "))
        online_orders.append({"order_id": order_id, "delivery_time": delivery_time})

    print("\nBefore sorting:")
    for order in online_orders:
        print(order)

    merge_sort(online_orders)

    print("\nAfter sorting by delivery time (quickest first):")
    for order in online_orders:
        print(order)

