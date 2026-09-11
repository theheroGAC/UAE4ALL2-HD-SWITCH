import urllib.request
import xml.etree.ElementTree as ET
import re
import json
import os

def clean_title(raw_title):
    t = raw_title
    while True:
        stripped = re.sub(r'\s*[\(\[].*?[\)\]]\s*$', '', t).strip()
        if stripped == t:
            break
        t = stripped
    t = re.sub(r'\s*-\s*Disk\s*\d+.*$', '', t, flags=re.IGNORECASE).strip()
    return t.strip()

CURATED = {
    "Turrican": { "title": "Turrican", "year": 1990, "developer": "Rainbow Arts", "publisher": "Rainbow Arts", "genre": "Run and Gun", "players": "1" },
    "Turrican 2": { "title": "Turrican II: The Final Fight", "year": 1991, "developer": "Factor 5", "publisher": "Rainbow Arts", "genre": "Run and Gun", "players": "1" },
    "Turrican II": { "title": "Turrican II: The Final Fight", "year": 1991, "developer": "Factor 5", "publisher": "Rainbow Arts", "genre": "Run and Gun", "players": "1" },
    "Turrican 3": { "title": "Turrican 3: Payment Day", "year": 1993, "developer": "Factor 5", "publisher": "Rainbow Arts", "genre": "Run and Gun", "players": "1" },
    "Turrican III": { "title": "Turrican 3: Payment Day", "year": 1993, "developer": "Factor 5", "publisher": "Rainbow Arts", "genre": "Run and Gun", "players": "1" },
    "SWIV": { "title": "SWIV", "year": 1991, "developer": "Random Logic", "publisher": "Sales Curve", "genre": "Shoot 'em up", "players": "1-2" },
    "Sensible Soccer": { "title": "Sensible Soccer", "year": 1992, "developer": "Sensible Software", "publisher": "Renegade", "genre": "Sports / Soccer", "players": "1-2" },
    "Sensible World of Soccer": { "title": "Sensible World of Soccer", "year": 1994, "developer": "Sensible Software", "publisher": "Renegade", "genre": "Sports / Soccer", "players": "1-2" },
    "SWOS": { "title": "Sensible World of Soccer", "year": 1994, "developer": "Sensible Software", "publisher": "Renegade", "genre": "Sports / Soccer", "players": "1-2" },
    "Alien Breed": { "title": "Alien Breed", "year": 1991, "developer": "Team17", "publisher": "Team17", "genre": "Top-Down Shooter", "players": "1-2" },
    "Alien Breed Special Edition": { "title": "Alien Breed Special Edition 92", "year": 1992, "developer": "Team17", "publisher": "Team17", "genre": "Top-Down Shooter", "players": "1-2" },
    "Alien Breed 92": { "title": "Alien Breed Special Edition 92", "year": 1992, "developer": "Team17", "publisher": "Team17", "genre": "Top-Down Shooter", "players": "1-2" },
    "Alien Breed II": { "title": "Alien Breed II: The Horror Continues", "year": 1993, "developer": "Team17", "publisher": "Team17", "genre": "Top-Down Shooter", "players": "1-2" },
    "Alien Breed 2": { "title": "Alien Breed II: The Horror Continues", "year": 1993, "developer": "Team17", "publisher": "Team17", "genre": "Top-Down Shooter", "players": "1-2" },
    "Alien Breed Tower Assault": { "title": "Alien Breed: Tower Assault", "year": 1994, "developer": "Team17", "publisher": "Team17", "genre": "Top-Down Shooter", "players": "1-2" },
    "Alien Breed 3D": { "title": "Alien Breed 3D", "year": 1995, "developer": "Team17", "publisher": "Ocean", "genre": "First-Person Shooter", "players": "1" },
    "Speedball": { "title": "Speedball", "year": 1988, "developer": "Bitmap Brothers", "publisher": "Image Works", "genre": "Sports / Action", "players": "1-2" },
    "Speedball 2": { "title": "Speedball 2: Brutal Deluxe", "year": 1990, "developer": "Bitmap Brothers", "publisher": "Image Works", "genre": "Sports / Action", "players": "1-2" },
    "Speedball 2 Brutal Deluxe": { "title": "Speedball 2: Brutal Deluxe", "year": 1990, "developer": "Bitmap Brothers", "publisher": "Image Works", "genre": "Sports / Action", "players": "1-2" },
    "Cannon Fodder": { "title": "Cannon Fodder", "year": 1993, "developer": "Sensible Software", "publisher": "Virgin", "genre": "Action / Strategy", "players": "1" },
    "Cannon Fodder 2": { "title": "Cannon Fodder 2", "year": 1994, "developer": "Sensible Software", "publisher": "Virgin", "genre": "Action / Strategy", "players": "1" },
    "Lemmings": { "title": "Lemmings", "year": 1991, "developer": "DMA Design", "publisher": "Psygnosis", "genre": "Puzzle", "players": "1-2" },
    "Lemmings 2": { "title": "Lemmings 2: The Tribes", "year": 1993, "developer": "DMA Design", "publisher": "Psygnosis", "genre": "Puzzle", "players": "1" },
    "Oh No More Lemmings": { "title": "Oh No! More Lemmings", "year": 1991, "developer": "DMA Design", "publisher": "Psygnosis", "genre": "Puzzle", "players": "1-2" },
    "Monkey Island": { "title": "The Secret of Monkey Island", "year": 1990, "developer": "Lucasfilm Games", "publisher": "Lucasfilm Games", "genre": "Point & Click Adventure", "players": "1" },
    "Secret of Monkey Island": { "title": "The Secret of Monkey Island", "year": 1990, "developer": "Lucasfilm Games", "publisher": "Lucasfilm Games", "genre": "Point & Click Adventure", "players": "1" },
    "Monkey Island 2": { "title": "Monkey Island 2: LeChuck's Revenge", "year": 1991, "developer": "LucasArts", "publisher": "LucasArts", "genre": "Point & Click Adventure", "players": "1" },
    "Another World": { "title": "Another World", "year": 1991, "developer": "Delphine Software", "publisher": "Delphine Software", "genre": "Cinematic Platformer", "players": "1" },
    "Flashback": { "title": "Flashback: The Quest for Identity", "year": 1992, "developer": "Delphine Software", "publisher": "U.S. Gold", "genre": "Cinematic Platformer", "players": "1" },
    "Shadow of the Beast": { "title": "Shadow of the Beast", "year": 1989, "developer": "Reflections", "publisher": "Psygnosis", "genre": "Action / Platformer", "players": "1" },
    "Shadow of the Beast II": { "title": "Shadow of the Beast II", "year": 1990, "developer": "Reflections", "publisher": "Psygnosis", "genre": "Action / Adventure", "players": "1" },
    "Shadow of the Beast 2": { "title": "Shadow of the Beast II", "year": 1990, "developer": "Reflections", "publisher": "Psygnosis", "genre": "Action / Adventure", "players": "1" },
    "Shadow of the Beast III": { "title": "Shadow of the Beast III", "year": 1992, "developer": "Reflections", "publisher": "Psygnosis", "genre": "Action / Adventure", "players": "1" },
    "Superfrog": { "title": "Superfrog", "year": 1993, "developer": "Team17", "publisher": "Team17", "genre": "Platformer", "players": "1" },
    "Lotus Esprit Turbo Challenge": { "title": "Lotus Esprit Turbo Challenge", "year": 1990, "developer": "Magnetic Fields", "publisher": "Gremlin Graphics", "genre": "Racing", "players": "1-2" },
    "Lotus Turbo Challenge 2": { "title": "Lotus Turbo Challenge 2", "year": 1991, "developer": "Magnetic Fields", "publisher": "Gremlin Graphics", "genre": "Racing", "players": "1-2" },
    "Lotus 2": { "title": "Lotus Turbo Challenge 2", "year": 1991, "developer": "Magnetic Fields", "publisher": "Gremlin Graphics", "genre": "Racing", "players": "1-2" },
    "Lotus III": { "title": "Lotus III: The Ultimate Challenge", "year": 1992, "developer": "Magnetic Fields", "publisher": "Gremlin Graphics", "genre": "Racing", "players": "1-2" },
    "Lotus 3": { "title": "Lotus III: The Ultimate Challenge", "year": 1992, "developer": "Magnetic Fields", "publisher": "Gremlin Graphics", "genre": "Racing", "players": "1-2" },
    "Dune": { "title": "Dune", "year": 1992, "developer": "Cryo Interactive", "publisher": "Virgin", "genre": "Adventure / Strategy", "players": "1" },
    "Dune II": { "title": "Dune II: The Battle for Arrakis", "year": 1992, "developer": "Westwood Studios", "publisher": "Virgin", "genre": "Real-Time Strategy", "players": "1" },
    "Dune 2": { "title": "Dune II: The Battle for Arrakis", "year": 1992, "developer": "Westwood Studios", "publisher": "Virgin", "genre": "Real-Time Strategy", "players": "1" },
    "The Settlers": { "title": "The Settlers", "year": 1993, "developer": "Blue Byte", "publisher": "Blue Byte", "genre": "Strategy / Simulation", "players": "1-2" },
    "Settlers": { "title": "The Settlers", "year": 1993, "developer": "Blue Byte", "publisher": "Blue Byte", "genre": "Strategy / Simulation", "players": "1-2" },
    "Worms": { "title": "Worms", "year": 1995, "developer": "Team17", "publisher": "Ocean", "genre": "Turn-Based Strategy", "players": "1-4" },
    "Worms The Directors Cut": { "title": "Worms: The Director's Cut", "year": 1997, "developer": "Team17", "publisher": "Ocean", "genre": "Turn-Based Strategy", "players": "1-4" },
    "Pinball Dreams": { "title": "Pinball Dreams", "year": 1992, "developer": "Digital Illusions", "publisher": "21st Century", "genre": "Pinball", "players": "1-8" },
    "Pinball Fantasies": { "title": "Pinball Fantasies", "year": 1992, "developer": "Digital Illusions", "publisher": "21st Century", "genre": "Pinball", "players": "1-8" },
    "Pinball Illusions": { "title": "Pinball Illusions", "year": 1995, "developer": "Digital Illusions", "publisher": "21st Century", "genre": "Pinball", "players": "1-8" },
    "Slam Tilt": { "title": "Slam Tilt", "year": 1996, "developer": "Liquid Hollywood", "publisher": "21st Century", "genre": "Pinball", "players": "1-8" },
    "Gods": { "title": "Gods", "year": 1991, "developer": "Bitmap Brothers", "publisher": "Renegade", "genre": "Platform / Action", "players": "1" },
    "The Chaos Engine": { "title": "The Chaos Engine", "year": 1993, "developer": "Bitmap Brothers", "publisher": "Renegade", "genre": "Top-Down Shooter", "players": "1-2" },
    "Chaos Engine": { "title": "The Chaos Engine", "year": 1993, "developer": "Bitmap Brothers", "publisher": "Renegade", "genre": "Top-Down Shooter", "players": "1-2" },
    "Chaos Engine 2": { "title": "The Chaos Engine 2", "year": 1996, "developer": "Bitmap Brothers", "publisher": "Renegade", "genre": "Top-Down Shooter", "players": "1-2" },
    "Xenon 2": { "title": "Xenon 2: Megablast", "year": 1989, "developer": "Bitmap Brothers", "publisher": "Image Works", "genre": "Shoot 'em up", "players": "1-2" },
    "Xenon 2 Megablast": { "title": "Xenon 2: Megablast", "year": 1989, "developer": "Bitmap Brothers", "publisher": "Image Works", "genre": "Shoot 'em up", "players": "1-2" },
    "Moonstone": { "title": "Moonstone: A Hard Days Knight", "year": 1991, "developer": "Mind's Eye", "publisher": "Mindscape", "genre": "Action / RPG", "players": "1-4" },
    "Wings": { "title": "Wings", "year": 1990, "developer": "Cinemaware", "publisher": "Cinemaware", "genre": "Flight Action", "players": "1" },
    "It Came From The Desert": { "title": "It Came from the Desert", "year": 1989, "developer": "Cinemaware", "publisher": "Cinemaware", "genre": "Action / Adventure", "players": "1" },
    "Defender of the Crown": { "title": "Defender of the Crown", "year": 1986, "developer": "Cinemaware", "publisher": "Cinemaware", "genre": "Strategy / Action", "players": "1" },
    "Golden Axe": { "title": "Golden Axe", "year": 1990, "developer": "Probe Software", "publisher": "Virgin", "genre": "Beat 'em up", "players": "1-2" },
    "Final Fight": { "title": "Final Fight", "year": 1991, "developer": "U.S. Gold", "publisher": "Capcom", "genre": "Beat 'em up", "players": "1-2" },
    "Syndicate": { "title": "Syndicate", "year": 1993, "developer": "Bullfrog", "publisher": "Electronic Arts", "genre": "Tactical Strategy", "players": "1" },
    "Theme Park": { "title": "Theme Park", "year": 1994, "developer": "Bullfrog", "publisher": "Electronic Arts", "genre": "Simulation", "players": "1" },
    "Populous": { "title": "Populous", "year": 1989, "developer": "Bullfrog", "publisher": "Electronic Arts", "genre": "God Game / Strategy", "players": "1-2" },
    "Populous II": { "title": "Populous II: Trials of the Olympian Gods", "year": 1991, "developer": "Bullfrog", "publisher": "Electronic Arts", "genre": "God Game / Strategy", "players": "1-2" },
    "Populous 2": { "title": "Populous II: Trials of the Olympian Gods", "year": 1991, "developer": "Bullfrog", "publisher": "Electronic Arts", "genre": "God Game / Strategy", "players": "1-2" },
    "Civilization": { "title": "Sid Meier's Civilization", "year": 1992, "developer": "MicroProse", "publisher": "MicroProse", "genre": "Turn-Based Strategy", "players": "1" },
    "Simon the Sorcerer": { "title": "Simon the Sorcerer", "year": 1993, "developer": "Adventure Soft", "publisher": "Adventure Soft", "genre": "Point & Click Adventure", "players": "1" },
    "Eye of the Beholder": { "title": "Eye of the Beholder", "year": 1991, "developer": "Westwood Studios", "publisher": "SSI", "genre": "Dungeon Crawler RPG", "players": "1" },
    "Eye of the Beholder II": { "title": "Eye of the Beholder II: The Crimson Cloak", "year": 1992, "developer": "Westwood Studios", "publisher": "SSI", "genre": "Dungeon Crawler RPG", "players": "1" },
    "Jaguar XJ220": { "title": "Jaguar XJ220", "year": 1992, "developer": "Core Design", "publisher": "Core Design", "genre": "Racing", "players": "1-2" },
    "Super Cars II": { "title": "Super Cars II", "year": 1991, "developer": "Gremlin Graphics", "publisher": "Gremlin Graphics", "genre": "Top-Down Racing", "players": "1-2" },
    "Super Cars 2": { "title": "Super Cars II", "year": 1991, "developer": "Gremlin Graphics", "publisher": "Gremlin Graphics", "genre": "Top-Down Racing", "players": "1-2" },
    "Project X": { "title": "Project-X", "year": 1992, "developer": "Team17", "publisher": "Team17", "genre": "Shoot 'em up", "players": "1-2" },
    "Zool": { "title": "Zool: Ninja of the Nth Dimension", "year": 1992, "developer": "Gremlin Graphics", "publisher": "Gremlin Graphics", "genre": "Platformer", "players": "1" },
    "Zool 2": { "title": "Zool 2", "year": 1993, "developer": "Gremlin Graphics", "publisher": "Gremlin Graphics", "genre": "Platformer", "players": "1-2" },
    "Ruff n Tumble": { "title": "Ruff 'n' Tumble", "year": 1994, "developer": "Wunderkind", "publisher": "Renegade", "genre": "Run and Gun", "players": "1" },
    "Lionheart": { "title": "Lionheart", "year": 1993, "developer": "Thalion", "publisher": "Thalion", "genre": "Platformer / Action", "players": "1" },
    "North & South": { "title": "North & South", "year": 1989, "developer": "Infogrames", "publisher": "Infogrames", "genre": "Strategy / Action", "players": "1-2" },
    "North and South": { "title": "North & South", "year": 1989, "developer": "Infogrames", "publisher": "Infogrames", "genre": "Strategy / Action", "players": "1-2" },
    "Kick Off 2": { "title": "Kick Off 2", "year": 1990, "developer": "Dino Dini", "publisher": "Anco", "genre": "Sports / Soccer", "players": "1-2" },
    "Hybris": { "title": "Hybris", "year": 1988, "developer": "SPS Software", "publisher": "Discovery", "genre": "Vertical Shoot 'em up", "players": "1-2" },
    "Battle Squadron": { "title": "Battle Squadron", "year": 1989, "developer": "Cope-Com", "publisher": "Electronic Arts", "genre": "Vertical Shoot 'em up", "players": "1-2" },
    "James Pond 2": { "title": "James Pond 2: Codename RoboCod", "year": 1991, "developer": "Vectordean", "publisher": "Millennium", "genre": "Platformer", "players": "1" },
    "Robocod": { "title": "James Pond 2: Codename RoboCod", "year": 1991, "developer": "Vectordean", "publisher": "Millennium", "genre": "Platformer", "players": "1" },
    "James Pond": { "title": "James Pond: Underwater Agent", "year": 1990, "developer": "Millennium", "publisher": "Millennium", "genre": "Platformer", "players": "1" },
    "Rick Dangerous": { "title": "Rick Dangerous", "year": 1989, "developer": "Core Design", "publisher": "Firebird", "genre": "Platformer", "players": "1" },
    "Rick Dangerous 2": { "title": "Rick Dangerous 2", "year": 1990, "developer": "Core Design", "publisher": "Micro Style", "genre": "Platformer", "players": "1" },
    "Stunt Car Racer": { "title": "Stunt Car Racer", "year": 1989, "developer": "Geoff Crammond", "publisher": "Micro Style", "genre": "Racing", "players": "1-2" },
    "IK+": { "title": "International Karate +", "year": 1988, "developer": "Archer Maclean", "publisher": "System 3", "genre": "Fighting", "players": "1-2" },
    "International Karate +": { "title": "International Karate +", "year": 1988, "developer": "Archer Maclean", "publisher": "System 3", "genre": "Fighting", "players": "1-2" },
    "Giana Sisters": { "title": "The Great Giana Sisters", "year": 1987, "developer": "Time Warp", "publisher": "Rainbow Arts", "genre": "Platformer", "players": "1-2" },
    "The Great Giana Sisters": { "title": "The Great Giana Sisters", "year": 1987, "developer": "Time Warp", "publisher": "Rainbow Arts", "genre": "Platformer", "players": "1-2" },
    "Desert Strike": { "title": "Desert Strike: Return to the Gulf", "year": 1992, "developer": "Electronic Arts", "publisher": "Electronic Arts", "genre": "Action / Shooter", "players": "1" },
    "Jungle Strike": { "title": "Jungle Strike", "year": 1993, "developer": "Electronic Arts", "publisher": "Electronic Arts", "genre": "Action / Shooter", "players": "1" },
    "Benefactor": { "title": "Benefactor", "year": 1994, "developer": "Digital Illusions", "publisher": "Psygnosis", "genre": "Platformer / Puzzle", "players": "1" },
    "Hunter": { "title": "Hunter", "year": 1991, "developer": "Paul Holmes", "publisher": "Activision", "genre": "3D Action / Adventure", "players": "1" },
    "Rainbow Islands": { "title": "Rainbow Islands", "year": 1990, "developer": "Taito", "publisher": "Ocean", "genre": "Platformer", "players": "1-2" },
    "Toki": { "title": "Toki", "year": 1991, "developer": "Ocean", "publisher": "Ocean", "genre": "Platformer / Action", "players": "1-2" },
    "Silkworm": { "title": "Silkworm", "year": 1989, "developer": "Tecmo", "publisher": "Virgin", "genre": "Side-Scrolling Shooter", "players": "1-2" },
    "Rodland": { "title": "Rodland", "year": 1991, "developer": "Jaleco", "publisher": "Storm", "genre": "Platformer", "players": "1-2" },
    "Parasol Stars": { "title": "Parasol Stars", "year": 1992, "developer": "Taito", "publisher": "Ocean", "genre": "Platformer", "players": "1-2" },
    "Wizkid": { "title": "Wizkid", "year": 1992, "developer": "Sensible Software", "publisher": "Ocean", "genre": "Puzzle / Action", "players": "1" },
    "Wizball": { "title": "Wizball", "year": 1988, "developer": "Sensible Software", "publisher": "Ocean", "genre": "Shoot 'em up", "players": "1-2" },
    "Midnight Resistance": { "title": "Midnight Resistance", "year": 1990, "developer": "Data East", "publisher": "Ocean", "genre": "Run and Gun", "players": "1-2" },
    "Chuck Rock": { "title": "Chuck Rock", "year": 1991, "developer": "Core Design", "publisher": "Core Design", "genre": "Platformer", "players": "1" },
    "Chuck Rock II": { "title": "Chuck Rock II: Son of Chuck", "year": 1993, "developer": "Core Design", "publisher": "Core Design", "genre": "Platformer", "players": "1" },
    "Cadaver": { "title": "Cadaver", "year": 1990, "developer": "Bitmap Brothers", "publisher": "Image Works", "genre": "Isometric Adventure", "players": "1" },
    "First Samurai": { "title": "The First Samurai", "year": 1991, "developer": "Vivid Image", "publisher": "Mirrorsoft", "genre": "Action / Platformer", "players": "1" },
    "Second Samurai": { "title": "The Second Samurai", "year": 1993, "developer": "Vivid Image", "publisher": "Psygnosis", "genre": "Action / Platformer", "players": "1-2" },
    "Fire & Ice": { "title": "Fire & Ice", "year": 1992, "developer": "Graftgold", "publisher": "Renegade", "genre": "Platformer", "players": "1" },
    "Fire and Ice": { "title": "Fire & Ice", "year": 1992, "developer": "Graftgold", "publisher": "Renegade", "genre": "Platformer", "players": "1" },
    "Super Skidmarks": { "title": "Super Skidmarks", "year": 1995, "developer": "Acid Software", "publisher": "Guildhall", "genre": "Top-Down Racing", "players": "1-8" },
    "Skidmarks": { "title": "Skidmarks", "year": 1993, "developer": "Acid Software", "publisher": "Acid Software", "genre": "Top-Down Racing", "players": "1-4" },
    "Banshee": { "title": "Banshee", "year": 1994, "developer": "Core Design", "publisher": "Core Design", "genre": "Vertical Shoot 'em up", "players": "1-2" },
    "Micro Machines": { "title": "Micro Machines", "year": 1993, "developer": "Codemasters", "publisher": "Codemasters", "genre": "Top-Down Racing", "players": "1-2" },
    "Frontier Elite II": { "title": "Frontier: Elite II", "year": 1993, "developer": "David Braben", "publisher": "Gametek", "genre": "Space Simulation", "players": "1" },
    "Elite": { "title": "Elite", "year": 1988, "developer": "David Braben", "publisher": "Firebird", "genre": "Space Simulation", "players": "1" },
    "Indianapolis 500": { "title": "Indianapolis 500: The Simulation", "year": 1989, "developer": "Papyrus", "publisher": "Electronic Arts", "genre": "Racing Simulator", "players": "1" },
    "Formula One Grand Prix": { "title": "Formula One Grand Prix", "year": 1991, "developer": "Geoff Crammond", "publisher": "MicroProse", "genre": "Racing Simulator", "players": "1" },
    "F1GP": { "title": "Formula One Grand Prix", "year": 1991, "developer": "Geoff Crammond", "publisher": "MicroProse", "genre": "Racing Simulator", "players": "1" },
    "Apidya": { "title": "Apidya", "year": 1992, "developer": "Kaiko", "publisher": "Play Byte", "genre": "Horizontal Shoot 'em up", "players": "1-2" },
    "Disposable Hero": { "title": "Disposable Hero", "year": 1993, "developer": "Euphoria", "publisher": "Psygnosis", "genre": "Horizontal Shoot 'em up", "players": "1" },
    "Agony": { "title": "Agony", "year": 1992, "developer": "Art & Magic", "publisher": "Psygnosis", "genre": "Horizontal Shoot 'em up", "players": "1" },
    "Super Stardust": { "title": "Super Stardust", "year": 1994, "developer": "Bloodhouse", "publisher": "Team17", "genre": "Multi-directional Shooter", "players": "1-2" },
    "Stardust": { "title": "Stardust", "year": 1993, "developer": "Bloodhouse", "publisher": "Daze", "genre": "Multi-directional Shooter", "players": "1" },
    "Oscar": { "title": "Oscar", "year": 1993, "developer": "Flair Software", "publisher": "Flair Software", "genre": "Platformer", "players": "1" },
    "Putty": { "title": "Putty", "year": 1992, "developer": "System 3", "publisher": "System 3", "genre": "Platformer", "players": "1" },
    "Putty Squad": { "title": "Putty Squad", "year": 1994, "developer": "System 3", "publisher": "System 3", "genre": "Platformer", "players": "1" },
    "Hired Guns": { "title": "Hired Guns", "year": 1993, "developer": "DMA Design", "publisher": "Psygnosis", "genre": "RPG / Action", "players": "1-4" },
    "Amberstar": { "title": "Amberstar", "year": 1992, "developer": "Thalion", "publisher": "Thalion", "genre": "RPG", "players": "1" },
    "Ambermoon": { "title": "Ambermoon", "year": 1993, "developer": "Thalion", "publisher": "Thalion", "genre": "RPG", "players": "1" },
    "Ishar": { "title": "Ishar: Legend of the Fortress", "year": 1992, "developer": "Silmarils", "publisher": "Silmarils", "genre": "RPG", "players": "1" },
    "Ishar 2": { "title": "Ishar 2: Messengers of Doom", "year": 1993, "developer": "Silmarils", "publisher": "Silmarils", "genre": "RPG", "players": "1" },
    "Ishar 3": { "title": "Ishar 3: The Seven Gates of Infinity", "year": 1994, "developer": "Silmarils", "publisher": "Silmarils", "genre": "RPG", "players": "1" },
    "Black Crypt": { "title": "Black Crypt", "year": 1992, "developer": "Raven Software", "publisher": "Electronic Arts", "genre": "Dungeon Crawler RPG", "players": "1" },
    "Traps n Treasures": { "title": "Traps 'n' Treasures", "year": 1993, "developer": "Roman Werner", "publisher": "Starbyte", "genre": "Action / Platformer", "players": "1" },
    "Flight of the Amazon Queen": { "title": "Flight of the Amazon Queen", "year": 1995, "developer": "Interactive Binary Illusions", "publisher": "Warner", "genre": "Point & Click Adventure", "players": "1" },
    "Beneath a Steel Sky": { "title": "Beneath a Steel Sky", "year": 1994, "developer": "Revolution Software", "publisher": "Virgin", "genre": "Point & Click Adventure", "players": "1" },
    "Brian the Lion": { "title": "Brian the Lion", "year": 1994, "developer": "Reflections", "publisher": "Psygnosis", "genre": "Platformer", "players": "1" },
    "Z-Out": { "title": "Z-Out", "year": 1990, "developer": "Advantec", "publisher": "Rainbow Arts", "genre": "Horizontal Shoot 'em up", "players": "1-2" },
    "X-Out": { "title": "X-Out", "year": 1989, "developer": "Rainbow Arts", "publisher": "Rainbow Arts", "genre": "Horizontal Shoot 'em up", "players": "1-2" }
}

xml_urls = [
    "https://raw.githubusercontent.com/mamedev/mame/master/hash/amigaocs_flop.xml",
    "https://raw.githubusercontent.com/mamedev/mame/master/hash/amigaaga_flop.xml",
    "https://raw.githubusercontent.com/mamedev/mame/master/hash/amigaecs_flop.xml",
    "https://raw.githubusercontent.com/mamedev/mame/master/hash/cd32.xml",
    "https://raw.githubusercontent.com/mamedev/mame/master/hash/amiga_flop.xml",
]

database = {}

for u in xml_urls:
    print(f"Reading {u.split('/')[-1]}...")
    try:
        req = urllib.request.Request(u, headers={'User-Agent': 'Mozilla/5.0'})
        content = urllib.request.urlopen(req, timeout=30).read()
        root = ET.fromstring(content)
        for s in root.findall('software'):
            desc = s.findtext('description', '').strip()
            year = s.findtext('year', '').strip()
            pub = s.findtext('publisher', '').strip()
            if not desc:
                continue
            
            cleaned = clean_title(desc)
            if not cleaned or len(cleaned) < 2:
                continue

            year_clean = re.sub(r'[^\d]', '', year) if year else ""
            if len(year_clean) >= 4 and year_clean[:4].startswith(('198', '199', '20')):
                year_val = int(year_clean[:4])
            else:
                year_val = 1990
            
            clean_pub = pub.replace('<unknown>', 'Amiga Publisher').strip()
            if not clean_pub:
                clean_pub = "Amiga Publisher"

            entry = {
                "title": cleaned,
                "year": year_val,
                "developer": clean_pub,
                "publisher": clean_pub,
                "genre": "Amiga Classic",
                "players": "1-2"
            }
            database[cleaned] = entry
    except Exception as e:
        print(f"Error {u}: {e}")

for k, v in CURATED.items():
    database[k] = v

print(f"Total database entries generated: {len(database)}")

out_path = "switchdata/data/gameinfo/games.json"
with open(out_path, "w", encoding="utf-8") as f:
    json.dump(database, f, indent=2, ensure_ascii=False)

print(f"Written successfully to {out_path} ({os.path.getsize(out_path)} bytes)")
