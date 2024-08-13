Keywords: C++, Graph theory, BFS

📝 Problem Statement:

You are tasked with implementing a function **std::list<Place> find_path(const Map &map)** that finds the shortest possible path in a given map of Grinch's lair, ensuring that the path collects at least one of each required item type. The path must start from a specific room, visit rooms to collect the necessary items, and end at another specified room. Each room is connected by corridors, and the path must respect these connections.

📥 Input:

The function will receive a Map structure that contains the following elements:
places: An integer representing the total number of rooms in Grinch's lair.
start: An integer representing the room number where Max (the character) begins his journey.
end: An integer representing the room number where Max must bring the collected items.
connections: A list of pairs of integers, where each pair (u, v) indicates a corridor between room u and room v.
items: A list of lists, where items[i] is a list of room numbers that contain the i-th type of item.

📤 Output:

The function should return a list of room numbers (std::list<Place>) representing the shortest path that:

Starts at map.start.
Ends at map.end.
Passes through rooms that allow collecting at least one of each item type.
Adheres to the available corridors between rooms 🔗.
If no such path exists that satisfies the above conditions, the function should return an empty list 🗑️.

⚙️ Constraints:

Room numbers are guaranteed to be within the range [0, places - 1].
The path must respect the connectivity of the rooms as defined by the connections list.
Each type of item may be available in multiple rooms, but the path must collect at least one of each type.

🧩 Example:

Given the following map structure:

places = 5

start = 0

end = 4

connections = [(0, 1), (1, 2), (2, 3), (3, 4), (1, 3)]

items = [[1, 2], [3, 4]]

The function should determine the shortest path 🛤️ that starts at room 0, ends at room 4, and collects at least one of each item type (0 and 1), using the available corridors.

Your task is to implement this function efficiently to handle varying map sizes and configurations 💻.
