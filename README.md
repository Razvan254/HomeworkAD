# HomeworkAD
Description:
This repository contains the code for a dynamic programming algorithm implemented in C, as well as Python, to optimize resource allocation among multiple employees based on the number of pages in books. Additionally, it includes a script to generate random datasets for testing the algorithm's performance.

Files:

    homework.c: This file contains the C implementation of the dynamic programming algorithm for resource allocation. It includes functions for dividing books among employees and calculating the optimal allocation.
    homework.py: This file contains the Python implementation of the same dynamic programming algorithm as in homework.c. It provides a translation of the C code into Python, ensuring the same functionality.
    datasets.c: This file contains the C code to generate random datasets for testing the algorithm. It randomly generates the number of books and assigns a random number of pages to each book, simulating real-world scenarios.

Usage:
    To compile and run the C implementation, use the following commands:
    bash

gcc homework.c -o homework
./homework

To run the Python implementation, simply execute:

python homework.py

To generate random datasets for testing, compile and run datasets.c:

bash
    gcc datasets.c -o datasets
    ./datasets

Contributing:
Contributions to improve the efficiency, functionality, or documentation of the code are welcome. Fork the repository, make your changes, and submit a pull request for review.
