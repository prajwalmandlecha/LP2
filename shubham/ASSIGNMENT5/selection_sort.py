def selection_sort(arr):
    """
    Selection Sort conceptually uses a Greedy approach by finding the 
    minimum element from the unsorted part and putting it at the beginning.
    """
    n = len(arr)
    # Traverse through all array elements
    for i in range(n):
        # Find the minimum element in remaining unsorted array
        min_idx = i
        for j in range(i + 1, n):
            if arr[j] < arr[min_idx]:
                min_idx = j
                
        # Swap the found minimum element with the first element
        arr[i], arr[min_idx] = arr[min_idx], arr[i]
        
    return arr

if __name__ == "__main__":
    while True:
        print("\n--- Selection Sort Menu ---")
        print("1. Run with sample array")
        print("2. Enter custom array")
        print("3. Exit")
        choice = input("Enter your choice (1-3): ")
        
        if choice == '1':
            sample_arr = [64, 25, 12, 22, 11]
            print(f"Original array: {sample_arr}")
            sorted_arr = selection_sort(sample_arr.copy())
            print(f"Sorted array:   {sorted_arr}")
        elif choice == '2':
            try:
                user_input = input("Enter numbers separated by space: ")
                arr = [int(x) for x in user_input.split()]
                print(f"Original array: {arr}")
                sorted_arr = selection_sort(arr.copy())
                print(f"Sorted array:   {sorted_arr}")
            except ValueError:
                print("Invalid input. Please enter integers only.")
        elif choice == '3':
            print("Exiting...")
            break
        else:
            print("Invalid choice. Please try again.")
