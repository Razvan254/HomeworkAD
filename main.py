# Function to find optimal cutting points using dynamic programming
def divide_books(books):
    num_books = len(books)
    cumulative_sums = [0] * num_books

    # Calculating cumulative sums of pages
    cumulative_sums[0] = books[0]
    for i in range(1, num_books):
        cumulative_sums[i] = cumulative_sums[i - 1] + books[i]

    dp = [[float('inf')] * (NUM_EMPLOYEES + 1) for _ in range(num_books + 1)]
    parent = [[-1] * (NUM_EMPLOYEES + 1) for _ in range(num_books + 1)]

    # Initialization
    for i in range(num_books + 1):
        dp[i][0] = 0

    # Calculating DP values
    for j in range(1, NUM_EMPLOYEES + 1):
        for i in range(1, num_books + 1):
            for k in range(i):
                cost = cumulative_sums[i - 1] if k == 0 else cumulative_sums[i - 1] - cumulative_sums[k - 1]
                if dp[i][j] > max(dp[k][j - 1], cost):
                    dp[i][j] = max(dp[k][j - 1], cost)
                    parent[i][j] = k

    # Reconstructing cutting points
    limits = [0] * (NUM_EMPLOYEES - 1)
    idx = num_books
    for j in range(NUM_EMPLOYEES, 1, -1):
        limits[j - 2] = parent[idx][j] - 1
        idx = parent[idx][j]

    # Calculating sums for each employee
    sums = [0] * NUM_EMPLOYEES
    for i in range(NUM_EMPLOYEES):
        start = 0 if i == 0 else limits[i - 1] + 1
        end = num_books - 1 if i == NUM_EMPLOYEES - 1 else limits[i]
        for j in range(start, end + 1):
            sums[i] += books[j]

    return limits, sums

if __name__ == "__main__":
    # Input number of books
    num_books = int(input("Enter the number of books: "))

    # Input number of pages for each book
    print("Enter the number of pages for each book:")
    books = []
    for i in range(num_books):
        book_pages = int(input(f"Book {i + 1}: "))
        books.append(book_pages)

    # Allocating pages for each employee
    NUM_EMPLOYEES = 3
    limits, sums = divide_books(books)

    # Displaying each employee's workload and sum of pages
    print("\nWorkload for each employee:")
    for i in range(NUM_EMPLOYEES):
        start = 0 if i == 0 else limits[i - 1] + 1
        end = num_books - 1 if i == NUM_EMPLOYEES - 1 else limits[i]
        employee_books = books[start:end + 1]
        total_pages = sum(employee_books)
        print(f"Employee {i + 1}: {' '.join(map(str, employee_books))} (Total: {total_pages} pages)")
