import Foundation

struct Place {
    let id: Int
    let type: String
    let name: String
    let rating: Int // 1 to 5
}

struct Municipality {
    let id: Int
    let name: String
    let description: String
    let coordinates: (latitude: Double, longitude: Double)
    let tags: [String]
    var spots: [Place] = []
}

var municipalities: [Municipality] = [
    Municipality(id: 1, name: "Gdańsk", description: "Port city rich in history", coordinates: (54.3521, 18.6467), tags: ["coastal", "heritage", "culture"]),
    Municipality(id: 2, name: "Kraków", description: "Poland’s cultural heart", coordinates: (50.0614, 19.9372), tags: ["culture", "history", "nightlife"]),
    Municipality(id: 3, name: "Warsaw", description: "Dynamic capital city", coordinates: (52.2298, 21.0123), tags: ["modern", "business", "culture"]),
    Municipality(id: 4, name: "Wrocław", description: "Architectural gem of Poland", coordinates: (51.1080, 17.0386), tags: ["architecture", "culture", "nightlife"]),
    Municipality(id: 5, name: "Poznań", description: "Famous for its old town charm", coordinates: (52.4065, 16.9253), tags: ["business", "history", "culture"])
]

municipalities[0].spots = [
    Place(id: 1, type: "restaurant", name: "Baltic Feast", rating: 5),
    Place(id: 2, type: "museum", name: "Maritime Heritage Center", rating: 4)
]

municipalities[1].spots = [
    Place(id: 3, type: "restaurant", name: "Cracovian Flavors", rating: 4),
    Place(id: 4, type: "bar", name: "Historic Pub", rating: 5)
]

municipalities[2].spots = [
    Place(id: 5, type: "restaurant", name: "Capital Gourmet", rating: 5),
    Place(id: 6, type: "museum", name: "Polish National Museum", rating: 5)
]

func filterByKeyword(keyword: String, in list: [Municipality]) -> [Municipality] {
    return list.filter { $0.tags.contains { $0.lowercased() == keyword.lowercased() } }
}

func locateMunicipality(named query: String, in list: [Municipality]) -> [Municipality] {
    return list.filter { $0.name.lowercased().contains(query.lowercased()) }
}

func computeDistance(from lat1: Double, lon1: Double, to lat2: Double, lon2: Double) -> Double {
    let R = 6371.0 // Earth radius in km
    let dLat = (lat2 - lat1) * .pi / 180
    let dLon = (lon2 - lon1) * .pi / 180
    let a = sin(dLat/2) * sin(dLat/2) + cos(lat1 * .pi / 180) * cos(lat2 * .pi / 180) * sin(dLon/2) * sin(dLon/2)
    let c = 2 * atan2(sqrt(a), sqrt(1-a))
    return R * c
}

func findNearestAndFarthest(from lat: Double, lon: Double, in list: [Municipality]) -> (nearest: Municipality?, farthest: Municipality?) {
    var nearest: Municipality? = nil
    var farthest: Municipality? = nil
    var minDist = Double.greatestFiniteMagnitude
    var maxDist = 0.0
    
    for city in list {
        let dist = computeDistance(from: lat, lon1: lon, to: city.coordinates.latitude, lon2: city.coordinates.longitude)
        if dist < minDist {
            minDist = dist
            nearest = city
        }
        if dist > maxDist {
            maxDist = dist
            farthest = city
        }
    }
    return (nearest, farthest)
}

func topRatedPlaces(in city: Municipality) -> [Place] {
    return city.spots.sorted { $0.rating > $1.rating }
}

func citiesWithFiveStarRestaurants(in list: [Municipality]) {
    let filteredCities = list.filter { city in
        city.spots.contains { $0.type == "restaurant" && $0.rating == 5 }
    }
    
    print("\nCities with 5-star restaurants:")
    for city in filteredCities {
        print("•", city.name)
    }
}

func sortedPlaces(in city: Municipality) -> [Place] {
    return city.spots.sorted { $0.rating > $1.rating }
}

func displayCitiesWithFiveStarLocations(in list: [Municipality]) {
    print("\nCities with five-star locations:")
    for city in list {
        let fiveStarPlaces = city.spots.filter { $0.rating == 5 }
        if !fiveStarPlaces.isEmpty {
            print("City: \(city.name) has \(fiveStarPlaces.count) five-star location(s):")
            for place in fiveStarPlaces {
                print(" - \(place.name) (\(place.type))")
            }
        }
    }
}

print("\nSearching for cities by keyword 'history':")
for city in filterByKeyword(keyword: "history", in: municipalities) {
    print("•", city.name)
}

print("\nFinding the closest and farthest municipalities from (52.0, 19.0):")
let closestAndFarthest = findNearestAndFarthest(from: 52.0, lon: 19.0, in: municipalities)
if let nearest = closestAndFarthest.nearest, let farthest = closestAndFarthest.farthest {
    print("Nearest: \(nearest.name)")
    print("Farthest: \(farthest.name)")
}

print("\nTop-rated places in Warsaw:")
if let warsaw = locateMunicipality(named: "Warsaw", in: municipalities).first {
    for place in topRatedPlaces(in: warsaw) {
        print("• \(place.name) - \(place.rating) stars")
    }
}

citiesWithFiveStarRestaurants(in: municipalities)

print("\nRelated locations of Gdańsk:")
if let gdansk = locateMunicipality(named: "Gdańsk", in: municipalities).first {
    for place in sortedPlaces(in: gdansk){
        print("• \(place.name) - \(place.rating) stars (\(place.type))")
    }
}

displayCitiesWithFiveStarLocations(in: municipalities)