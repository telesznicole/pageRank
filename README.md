# pageRank

This project implements a simplified PageRank ALgorithm using an adjacency list representation. This project, assigned in COP3530 Data Structures and Algorithms, sought for students to:<br>
*"[...] implement a simplified version of the original PageRank algorithm on which Google was built by representing the web as a graph and implementing this graph using an Adjacency List or an equivalent data structure. The PageRank algorithm is an algorithm that is used to order or rank different web pages on the internet."*

### Goals (as per project rubric):<br>
<b>Input</b><br>
Line 1 contains the number of lines (n) that will follow and the number of power iterations (p) you need to perform. Each line from 2 to n+1 will contain two URL’s – from_page to_page separated by a single space. This means that the from_page points to the URL to_page.<br>
<br><b>Output<b><br>
Print the PageRank of all pages after p powerIterations in ascending alphabetical order of webpage. Also, round off the rank of the page to two decimal places.<br>
<br><b>Constraints<b>
- 1 <= p <= 10,000
- 1 <= n <= 1,000,000
- 1 <= Unique webpages or |V| <= 1,000,000
