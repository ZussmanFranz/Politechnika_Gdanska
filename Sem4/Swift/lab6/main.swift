import Foundation

class MoominCharacter {
    let name: String
    
    var health: Int
    var max_health: Int
    let start_health: Int

    var friendship: Int
    let start_friendship: Int
    
    var level: Int = 1

    var journal: Array<String> = []

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
        print("\t\tHealth:\t\t\(health)")
        print("\t\tFriendship:\t\(friendship)")
    }

    func take_damage(damage: Int) {
        health = max(health - damage, 0)
        
        print("\nPlayer takes \(damage) damage\nNew health is \(health)")
    }

    func writeJournal(creature: Creature, encounter_result: Int) {
        let result_deskription: String

        switch (encounter_result) {
            case 1:
                result_deskription = " is calmed down"
            case 2:
                result_deskription = " was too scary"
            case 3:
                result_deskription = " made me feel sad :("
            default:
                result_deskription = " was... what was it?"
        }

        journal.append(creature.name + result_deskription)
    }

    func readJournal() {
        var counter: Int = 0

        for record in journal{
            counter += 1

            print(String(counter) + ": " + record)
        }
    }
}

class Creature {
    let name: String
    var mood: Int // hostility from 1 to 3
    var patience: Int // equivalent to health
    var max_patience: Int

    init (name: String, mood: Int, patience: Int){
        self.name = name
        self.mood = mood
        self.patience = patience
        max_patience = patience
    }

    func isCalm() -> Bool {
        return (patience > 0)
    }

    func drawStats() {
        print("\t\tName:\t\t\(name)")
        print("\t\tMood:\t\t\(mood)")
        print("\t\tPatience:\t\(patience)")
    }

    func take_damage(damage: Int) {
        patience = max(patience - damage, 0)
        
        print("\nCreature takes \(damage) calm points\nNew patience is \(patience)")
    }
}

func randomEncounter(playerLevel: Int) -> Creature {
    let possible_names = 
        ["Moomintroll", "Snufkin", "Little My", "Skoofkin", "Grinder Farmer", "Kroy Brothers"]

    let mood: Int = Int.random(in: 1...3) * playerLevel

    return Creature(name: possible_names.randomElement() ?? "Unknown",
        mood: mood, patience: Int.random(in: 50...100) * mood)
}

func playerChoice() -> Int {
    print("1 - Talk\n2 - Run away\n3 - Quit")

    var choice: Int = 0
    
    while (choice < 1 || choice > 3){
        print("\tenter your choice: ")
        choice = Int(readLine() ?? "pass") ?? 0
        print("You have entered: \(choice)") 
    }

    return choice
}

func run_away(player: MoominCharacter, creature: Creature) {
    if (Bool.random()) {
        print("Creature \(creature.name) scares \(player.name)")
        player.take_damage(damage: Int.random(in: 1...20))
    } else {
        print("\(player.name) successfully ran away from creature \(creature)")
    }
}

func talk(player: MoominCharacter, creature: Creature) -> Int {
    creature.take_damage(damage: player.friendship)
    if (!creature.isCalm()) {
        print("Creature \(creature.name) is calm now!")
        return 1
    } else {
        print("Creature \(creature.name) is still angry")
        player.take_damage(damage: creature.patience * creature.mood)

        if player.isHealthy() {
            return 0
        } else {
            return 3
        }
    }
}

// 0 == creature is still angry, 1 == creature calmed down, 2 == ran away from creature, 3 == creature finished the game
func playerAction(player: MoominCharacter, creature: Creature) -> Int {
    let choice = playerChoice()

    switch choice{
        case 3:
            // quit
            exit(1)
        case 2:
            // run away
            run_away(player: player, creature: creature)

            return 2
        default:
            // talk

            return talk(player: player, creature: creature)
    }
}

func gameLoop(name: String) -> MoominCharacter{
    let player = MoominCharacter(name: name, health: 100, friendship: 50)

    var creature: Creature = randomEncounter(playerLevel: player.level)
    // print("Creature encountered!")
    creature = randomEncounter(playerLevel: player.level)

    var encounter_result: Int

    while (player.isHealthy()) {
        player.drawCharacter()
        player.drawStats()

        print("\nCreature stats:")
        creature.drawStats()

        encounter_result = playerAction(player: player, creature: creature)

        if encounter_result == 1 {
            player.levelUp()
        }

        if encounter_result != 0 {
            player.writeJournal(creature: creature, encounter_result: encounter_result)

            // print("Creature encountered!")
            creature = randomEncounter(playerLevel: player.level)
        }
    }

    return player
}

func main() {
    print("Enter your name: ")
    let name: String = readLine() ?? "default"

    let player: MoominCharacter = gameLoop(name: name)

    print("Game over, \(name)\nLevel reached: \(player.level)\nJournal:")
    player.readJournal()
}

main()