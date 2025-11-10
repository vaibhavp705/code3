def heapify(a, n, i):
    l, r, m = 2*i+1, 2*i+2, i
    if l < n and a[l] > a[m]: m = l
    if r < n and a[r] > a[m]: m = r
    if m != i:
        a[i], a[m] = a[m], a[i]
        heapify(a, n, m)

def heap_sort(a):
    n = len(a)
    for i in range(n//2-1, -1, -1):  # Step 1: Build max heap
        heapify(a, n, i)
    for i in range(n-1, 0, -1):      # Step 2: Extract elements
        a[0], a[i] = a[i], a[0]      # Move max to end
        heapify(a, i, 0)             # Restore heap for remaining elements

# Example
arr = [12, 11, 13, 5, 6, 7]
print("Original array:", arr)
heap_sort(arr)
print("Sorted array:", arr)
