#include <vector>
#include <string>

using namespace std;

vector<string> loadDocuments() {

    return {

        // ================= AI / ML =================

        "Machine learning is a branch of artificial intelligence that allows systems to learn patterns from data without explicit programming.",
        "Deep learning uses multi layered neural networks to solve complex problems in computer vision and natural language processing.",
        "Transformers are neural network architectures widely used in large language models and modern AI systems.",
        "Large language models are trained on massive datasets to generate human like text and answer questions.",
        "Embeddings convert text images or other data into high dimensional numerical vector representations.",
        "Semantic search improves retrieval quality by understanding contextual meaning instead of exact keyword matching.",
        "Retrieval augmented generation combines vector search with language models to improve factual responses.",
        "Computer vision enables machines to interpret images videos and visual patterns using deep learning.",
        "Natural language processing helps computers understand generate and analyze human language.",
        "Reinforcement learning trains intelligent agents through rewards and penalties in interactive environments.",
        "Recommendation systems use similarity search and user behavior to personalize content.",
        "TensorFlow is a popular machine learning framework used for deep learning applications.",
        "PyTorch is widely adopted in AI research because of its flexibility and dynamic computation graph.",
        "Neural networks learn complex relationships from training data using interconnected artificial neurons.",
        "Artificial intelligence is transforming industries such as healthcare finance and autonomous systems.",

        // ================= VECTOR DATABASES =================

        "Vector databases store embeddings efficiently and support similarity based retrieval for AI applications.",
        "Approximate nearest neighbor algorithms trade a small amount of accuracy for significantly faster search speed.",
        "HNSW is a graph based approximate nearest neighbor algorithm optimized for high dimensional vector retrieval.",
        "KD Trees work efficiently in low dimensional spaces but degrade in performance in high dimensional embeddings.",
        "Cosine similarity measures the angular similarity between two vectors and is commonly used for embeddings.",
        "Euclidean distance calculates straight line distance between vectors in multidimensional space.",
        "Indexes accelerate retrieval operations in databases and vector search systems.",
        "Vector similarity search powers semantic retrieval systems recommendation engines and AI assistants.",
        "Modern vector databases support billions of embeddings with low latency retrieval.",
        "Reranking improves retrieval quality by rescoring approximate nearest neighbor results exactly.",

        // ================= DATABASES =================

        "PostgreSQL is a powerful open source relational database known for reliability and advanced SQL support.",
        "MySQL is commonly used in web applications and online transaction processing systems.",
        "Redis is an in memory key value database widely used for caching pub sub messaging and fast retrieval.",
        "MongoDB is a NoSQL document database designed for scalability and flexible schemas.",
        "Databases use indexing to improve query performance and reduce retrieval time.",
        "Sharding distributes database data across multiple machines for scalability.",
        "Replication increases fault tolerance by maintaining multiple copies of data.",
        "SQL is a language used to query and manage relational databases.",
        "ACID properties ensure reliable transactions in relational database systems.",
        "B Trees are optimized data structures used in databases and file systems.",

        // ================= CLOUD / DEVOPS =================

        "Amazon Web Services provides scalable cloud infrastructure and computing services.",
        "Microsoft Azure offers cloud platforms for analytics storage AI and virtual machines.",
        "Google Cloud Platform provides distributed infrastructure and machine learning services.",
        "Docker packages applications into lightweight portable containers for deployment consistency.",
        "Kubernetes automates deployment scaling and management of containerized applications.",
        "Cloud computing provides on demand access to scalable computing resources over the internet.",
        "Microservices architecture divides applications into loosely coupled independent services.",
        "Load balancing distributes incoming network traffic across multiple servers.",
        "CI CD pipelines automate software testing integration and deployment workflows.",
        "Virtualization enables multiple operating systems to run on shared hardware resources.",

        // ================= NETWORKING =================

        "HTTP is the foundation of communication on the World Wide Web.",
        "HTTPS encrypts communication between clients and servers using secure protocols.",
        "TCP ensures reliable ordered delivery of packets across networks.",
        "UDP prioritizes speed and low latency over reliability in network communication.",
        "DNS converts domain names into IP addresses for internet routing.",
        "APIs allow software systems and services to communicate with each other.",
        "REST APIs use standard HTTP methods for client server communication.",
        "WebSockets enable real time bidirectional communication between applications.",
        "Bandwidth determines how much data can be transmitted over a network connection.",
        "Latency measures the delay between sending and receiving data over a network.",

        // ================= OPERATING SYSTEMS =================

        "Linux is widely used in servers cloud computing and embedded systems.",
        "Windows is a desktop operating system developed by Microsoft.",
        "Operating systems manage hardware resources processes memory and storage devices.",
        "Threads enable concurrent execution within applications for improved performance.",
        "Processes are running instances of programs managed by the operating system.",
        "Memory management is critical for efficient low level systems programming.",
        "File systems organize and manage persistent storage on disks.",
        "Shell scripting automates repetitive tasks in Unix based operating systems.",
        "Device drivers allow operating systems to communicate with hardware devices.",
        "Scheduling algorithms determine how CPU resources are allocated to processes.",

        // ================= DSA =================

        "Binary search efficiently finds elements in sorted arrays using divide and conquer.",
        "Breadth first search explores graph nodes level by level using queues.",
        "Depth first search explores graph structures recursively or using stacks.",
        "Dynamic programming solves problems with overlapping subproblems efficiently.",
        "Greedy algorithms make locally optimal choices at each step.",
        "Graphs consist of nodes connected through edges representing relationships.",
        "Hash maps provide near constant time complexity for insertions and lookups.",
        "Stacks follow the last in first out principle.",
        "Queues follow the first in first out principle.",
        "Trees represent hierarchical relationships in computer science.",

        // ================= SOFTWARE ENGINEERING =================

        "Git is a distributed version control system used for tracking source code changes.",
        "GitHub hosts collaborative software development projects and repositories.",
        "Object oriented programming organizes software using classes and objects.",
        "Functional programming emphasizes immutable data and pure functions.",
        "Software engineering focuses on building scalable maintainable reliable systems.",
        "Debugging is the process of identifying and fixing software defects.",
        "Unit testing verifies the correctness of individual software components.",
        "Software optimization improves execution speed memory efficiency and scalability.",
        "Open source software encourages transparency collaboration and community contributions.",
        "Scalability is essential for systems serving millions of users.",

        // ================= CYBERSECURITY =================

        "Encryption secures sensitive information by converting it into unreadable ciphertext.",
        "Cybersecurity protects systems networks and data from digital attacks.",
        "JWT tokens are commonly used for authentication in web applications.",
        "Multi factor authentication improves account security using multiple verification methods.",
        "Firewalls monitor and filter incoming and outgoing network traffic.",
        "VPNs provide encrypted communication channels over public internet connections.",
        "Malware includes harmful software such as ransomware spyware and viruses.",
        "Phishing attacks attempt to steal confidential information from users.",
        "Public key cryptography uses asymmetric keys for secure communication.",
        "Penetration testing identifies vulnerabilities in software systems and networks.",

        // ================= MODERN COMPUTING =================

        "Edge computing processes data near the source to reduce latency.",
        "Blockchain stores transactions in immutable decentralized ledgers.",
        "Quantum computing leverages quantum mechanics for complex computation.",
        "Big data technologies process and analyze massive datasets efficiently.",
        "Distributed systems operate across multiple machines connected through networks.",
        "Parallel computing speeds up heavy computations using multiple processors.",
        "Caching improves application performance by storing frequently accessed data.",
        "Search engines rely on indexing and retrieval algorithms to find information quickly.",
        "Chatbots use natural language processing to interact conversationally with users.",
        "Self driving cars depend heavily on artificial intelligence and sensor fusion."
    };
}