def job_scheduling(jobs, max_deadline):
    """
    Job Scheduling Problem using Greedy Algorithm.
    jobs: List of tuples (Job_ID, Deadline, Profit)
    Returns: The sequence of jobs that maximizes profit.
    """
    # Sort jobs in descending order of profit (Greedy approach)
    jobs.sort(key=lambda x: x[2], reverse=True)
    
    # Keep track of free time slots and the final job sequence
    slots = [False] * max_deadline
    job_sequence = ['-'] * max_deadline
    total_profit = 0
    
    for job_id, deadline, profit in jobs:
        # Find a free slot for this job (starting from the latest possible slot)
        # Note: deadline-1 is used to convert into 0-based indexing
        for j in range(min(max_deadline - 1, deadline - 1), -1, -1):
            if not slots[j]:
                slots[j] = True
                job_sequence[j] = job_id
                total_profit += profit
                break
                
    return job_sequence, total_profit

if __name__ == "__main__":
    while True:
        print("\n--- Job Scheduling Menu ---")
        print("1. Run with sample jobs")
        print("2. Enter custom jobs")
        print("3. Exit")
        choice = input("Enter your choice (1-3): ")
        
        if choice == '1':
            jobs = [
                ('A', 2, 100), 
                ('B', 1, 19), 
                ('C', 2, 27), 
                ('D', 1, 25), 
                ('E', 3, 15)
            ]
            max_d = 3
            sequence, profit = job_scheduling(jobs, max_d)
            print(f"Sample Jobs: {jobs}")
            print(f"Maximum profit sequence of jobs: {sequence}")
            print(f"Total Profit: {profit}")
        elif choice == '2':
            try:
                n = int(input("Enter number of jobs: "))
                jobs = []
                max_d = 0
                for i in range(n):
                    job_id = input(f"Enter Job ID for job {i+1}: ")
                    deadline = int(input(f"Enter deadline for job {i+1}: "))
                    profit = int(input(f"Enter profit for job {i+1}: "))
                    jobs.append((job_id, deadline, profit))
                    if deadline > max_d:
                        max_d = deadline
                sequence, profit = job_scheduling(jobs, max_d)
                print(f"Maximum profit sequence of jobs: {sequence}")
                print(f"Total Profit: {profit}")
            except ValueError:
                print("Invalid input.")
        elif choice == '3':
            print("Exiting...")
            break
        else:
            print("Invalid choice. Please try again.")
