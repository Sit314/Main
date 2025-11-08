from itertools import permutations

import folium
import openrouteservice
from geopy.geocoders import Nominatim

# Your OpenRouteService API key
ORS_API_KEY = "5b3ce3597851110001cf6248254c8a63bf4c412793fc4d9f7079e78f"

# Addresses
addresses = {
    "Sit": "הספורט 12, חיפה",
    "Blam": "בית אל 9, חיפה",
    "Jonch": "אידר 43, חיפה",
    # "Gersh": "HaYam Road 137, Haifa",
    # "Technion": "Malal 20, Haifa",
    # "Tal": "Hagalil 136, Haifa",
    "Tal": "גדליהו 33, חיפה",
    # "Boga": "Aba Hillel Silver 111, Haifa",
    # "Sister Gersh": "Rabin 9, Kiryat Ata",
    "Tama": "הלל 20, חיפה",
    "Mai": "R. do Bruxo 36, Portugal",
}

start_name = "Sit"
end_name = "Tal"

# Initialize geocoder and client
geolocator = Nominatim(user_agent="haifa_map_app")
client = openrouteservice.Client(key=ORS_API_KEY)
haifa_map = folium.Map(location=(32.81, 34.9896), zoom_start=14)

# Geocode and place markers
coords = {}
for name, address in addresses.items():
    location = geolocator.geocode(address)
    if not location:
        print(f"Failed for name {name}, address {address}")
    latlon = (location.latitude, location.longitude)
    coords[name] = latlon
    folium.Marker(latlon, popup=f"{name}: {address}", tooltip=address).add_to(haifa_map)

keys = list(coords.keys())
n = len(keys)

# Coordinates in (lon, lat) format
coords_list = [coords[k][::-1] for k in keys]

matrix = client.distance_matrix(
    locations=coords_list,
    profile="driving-car",
    metrics=["duration"],
    units="m",  # meters and minutes
    resolve_locations=True,
)

# matrix["durations"] is a 2D list of driving times in seconds
dist_matrix = [[duration / 60 for duration in row] for row in matrix["durations"]]


# For storing the overall best path info
overall_best_path = None
overall_best_time = float("inf")
overall_best_start = None

print("\nAll possible paths for each possible starting point:")

# Try each location as a start
for start in range(n):
    others = [i for i in range(n) if i != start]
    print(f"\nStarting at {keys[start]}:")
    best_path_for_start = None
    best_time_for_start = float("inf")

    for perm in permutations(others):
        path = [start] + list(perm)
        total_time = sum(dist_matrix[path[i]][path[i + 1]] for i in range(len(path) - 1))
        path_names = " → ".join(keys[i] for i in path)
        print(f"{path_names}: {total_time:.1f} min")

        if total_time < best_time_for_start:
            best_time_for_start = total_time
            best_path_for_start = path

    # Update overall best path if better
    if best_time_for_start < overall_best_time:
        overall_best_time = best_time_for_start
        overall_best_path = best_path_for_start
        overall_best_start = start

# Print overall best path info
print("\nOverall shortest path (any start):")
print("Start at", keys[overall_best_start])
print(" → ".join(keys[i] for i in overall_best_path))
print(f"Total driving time: {overall_best_time:.1f} minutes")

# Draw the overall best path on the map in red
for i in range(len(overall_best_path) - 1):
    start_coord = coords[keys[overall_best_path[i]]]
    end_coord = coords[keys[overall_best_path[i + 1]]]
    route = client.directions(
        coordinates=[start_coord[::-1], end_coord[::-1]],
        profile="driving-car",
        format="geojson",
    )
    route_coords = route["features"][0]["geometry"]["coordinates"]
    route_latlon = [(lat, lon) for lon, lat in route_coords]
    folium.PolyLine(
        locations=route_latlon,
        color="red",
        weight=4,
        opacity=0.8,
        tooltip=f"{keys[overall_best_path[i]]} → {keys[overall_best_path[i + 1]]}",
    ).add_to(haifa_map)

# Save the map
haifa_map.save("2025_H1/haifa_tsp_any_start_path.html")

start_idx = keys.index(start_name)
end_idx = keys.index(end_name)

middle_indices = [i for i in range(n) if i not in (start_idx, end_idx)]

paths_with_times = []
for perm in permutations(middle_indices):
    path = [start_idx] + list(perm) + [end_idx]
    total_time = sum(dist_matrix[path[i]][path[i + 1]] for i in range(len(path) - 1))
    paths_with_times.append((total_time, path))

paths_with_times.sort()

print(f"\nAll paths from '{start_name}' to '{end_name}' sorted by total time:")
for total_time, path in paths_with_times:
    path_names = " → ".join(keys[i] for i in path)
    print(f"{path_names}: {total_time:.1f} min")
