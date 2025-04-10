class MoominCharacter {
    let name: String
    
    var health: Int
    var max_health: Int
    let start_health: Int

    var friendship: Int
    let start_friendship: Int
    
    var level: Int = 1

    init(name: String, health: Int, friendship: Int){
        self.name = name
        
        self.health = health
        max_health = health
        start_health = health
        
        self.friendship = friendship
        start_friendship = friendship
    }

    func levelUp(){
        // Each level increases max_health and friendship by it's initial value
        level += 1

        max_health += start_health
        health = max_health

        friendship += start_friendship

        print("\t\tLevel Up!\n\t\tNew level: \(level)")
    }

    func isHealthy() -> Bool {
        return (health > 0)
    }

    func drawCharacter() {
        print("\n                 /|  /|")
        print("                J(|----.")
        print("               /   ))))))")
        print("              J    '`'`' \\")
        print("              F     (.) (.)--._")
        print("             /                 `.")
        print("            J                   |")
        print("            F       ._         .'")
        print("           J          `-.____.'")
        print("           F           \\")
        print("          J             \\\\")
        print("          |   .  `.      \\\\")
        print(" ,,,      |    `.  `.     L`")
        print("\\VVV'     |      `.  `    |`")
        print(" \\W|      J        ```    |")
        print("  `.    .' \\              F")
        print("    `--'    )    ___..-   ( .-")
        print("           /   .'     `. //' /")
        print("           `.  \\        `<_.'")
        print("             `._|\n")

    }

    func drawStats(){
        print("\t\tName:\t\t\(name)")
        print("\t\tLevel:\t\t\(level)")
        print("\t\tHealth:\t\(health)")
        print("\t\tFriendship:\t\(friendship)")
    }
}

var me: MoominCharacter = MoominCharacter(name: "Eugene", health: 50, friendship: 100)

me.levelUp()
me.levelUp()

me.drawCharacter()
me.drawStats()