**Final Project Pemrograman Lanjut**


## 1. PENDAHULUAN

**Exploration 22** adalah sebuah game RPG (Role-Playing Game) berbasis turn-based combat yang dibuat menggunakan C++ dan library SFML (Simple and Fast Multimedia Library).


## 2. DESKRIPSI PROYEK

**Exploration 22** adalah game petualangan di mana pemain memimpin sebuah party beranggotakan hingga 3 karakter untuk menjelajahi 5 lantai dungeon yang berbeda. Setiap lantai memiliki 5 langkah dengan berbagai jenis node yang memiliki tantangan dan reward yang berbeda.

### Konsep Dasar
- **Genre**: Turn-based RPG dengan elemen eksplorasi
- **Platform**: Desktop (Windows/Linux)

---

## 3. FITUR UTAMA

### 3.1 Sistem Karakter
- **4 Karakter Unik**: Arthesa, Ahmed, Perkia, dan Hamilla
- **Sistem Stats**: HP, ATK, DEF, MAG, RES 
- **Tipe Entity**: MORTAL, ETHEREAL, CONSTRUCT (rock-paper-scissors system)
- **Skill System**: Setiap karakter memiliki 4 kemampuan unik dengan AP cost berbeda

### 3.2 Sistem Pertarungan
- **Turn-based Combat**: Pemain dan musuh bergantian menyerang
- **AP System**: 6 Action Points per turn untuk strategi resource management
- **Damage Calculation**: Memiliki sedikit kompleksitas namun masih simpel

### 3.3 Sistem Eksplorasi
- **5 Lantai Dungeon**: Setiap lantai memiliki struktur unik
- **Node Types**: BATTLE, EVENT, SHOP, BOSS (SHOP dan BOSS belum terimplementasi)
- **Linear Progression**: Single → Branch → Single → Branch → Boss

### 3.4 Sistem Event
- **5 Random Events**: Scenario acak dengan pilihan
- **Character Progression**: Event memberikan upgrade permanent
- **Multiple Choices**: Setiap event memiliki 3 pilihan dengan konsekuensi berbeda
- **Story Elements**: Narasi yang memperkaya pengalaman bermain

---

## 4. ARSITEKTUR SISTEM

### 4.1 Design Patterns

#### State Pattern
```cpp
class State {
public:
    virtual void handleEvent(sf::RenderWindow&, sf::Event&) = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow&) = 0;
};
```
**Implementasi**:
- MenuState, FloorState, BattleState, EventState, PartySelectState
- Transisi state yang clean dan terorganisir
- Pemisahan state untuk tiap bagian berbeda

#### Factory Pattern
```cpp
const std::vector<std::function<std::unique_ptr<Enemy>()>> ENEMY_TEMPLATES = {
    makeGoblin, makeSkeleton, makeWitch, makeWizard, makeFireWorm
};
```
**Implementasi**:
- Musuh lebih mudah dibuat
- Scaling musuh bisa dilakukan (Belum diimplementasikan)



### 4.2 Class Hierarchy

```
Entity (Abstract Base)
├── Character (Abstract)
│   ├── Arthesa
│   ├── Ahmed
│   ├── Perkia
│   └── Hamilla
└── Enemy (Concrete)

Node (Abstract Base)
├── BattleNode
├── EventNode
├── ShopNode
└── BossNode
```

---

## 5. IMPLEMENTASI TEKNIS

### 5.1 Memory Management
- **Smart Pointers**: Banyak menggunakan `std::unique_ptr` dan `std::shared_ptr`
- **Tidak ada Memory Leaks**:Karena banyak menggunakan smart pointer serta proses pen-delete-an objek yang dibuat dalam fungsi yang rapih

### 5.2 Data Structures
```cpp
// Party management
std::vector<std::unique_ptr<Character>> members;

// Floor generation
std::vector<std::vector<std::unique_ptr<Node>>> steps;

// Enemy groups
std::vector<std::unique_ptr<Enemy>> enemies;
```


## 6. STRUKTUR FILE

```
FP_PROGLAN/src/
├── main.cpp                    # Entry point
├── Assets/                     # Game assets
│   ├── Img/                   # Sprites dan backgrounds
│   └── Music/                 # Audio files
├── Battle/                     # Combat system
│   ├── party.h
│   ├── enemy_group.h
│   └── enemy_templates.cpp
├── Entity/                     # Character & enemy classes
│   ├── base.h/cpp
│   ├── character.h
│   ├── enemies.h
│   └── Character-Specified/
├── Floor/                      # Dungeon generation
│   ├── floor.h/cpp
├── Game/                       # Core engine
│   ├── game.h/cpp
├── Node/                       # Node system
│   ├── node.h
│   ├── BattleNode.h
│   ├── EventNode.h
│   └── BossNode.h
├── State/                      # State management
│   ├── state.h
│   ├── MenuState.h/cpp
│   ├── BattleState.h/cpp
│   ├── FloorState.h/cpp
│   └── EventState.h/cpp
└── include/                    # Headers
    ├── base.h
    └── others.h
```

---

## 7. GAMEPLAY DAN MEKANIK

### 7.1 Flow Permainan
1. **Main Menu**: Pemilihan "Begin Exploration" atau "Exit"
2. **Party Selection**: Pemilihan hingga 3 karakter dari 4 yang tersedia
3. **Floor Navigation**: Eksplorasi node-node di setiap lantai
4. **Combat/Events**: Interaksi dengan content di setiap node
5. **Progression**: Advancement ke lantai selanjutnya

### 7.2 Combat System
```
Player Turn:
├── Character Selection (UP/DOWN)
├── Action Selection (Attack/Skill1/Skill2/Skill3)
├── Target Selection (Enemy selection)
└── Action Resolution

Enemy Turn:
├── Random Target Selection
├── Random Attack Choice
└── Damage Application
```

### 7.3 Character Progression
- **Event-based Upgrades**: Permanent stat increases melalui events
- **No Traditional Leveling**: Progression melalui events bukan dari leveling

### 7.4 Enemy System
- **5 Enemy Types**: Goblin, Skeleton, Witch, Wizard, Fire Worm
- **Randomized Encounters**: 2-3 enemies per battle node

---

## 8. KESIMPULAN

### 8.1 Pencapaian Proyek
**Exploration 22** berhasil mengimplementasikan:
- ✅ Object-oriented design dengan inheritance
- ✅ Memory-safe programming dengan smart pointers
- ✅ Modular architecture untuk memudahkan pengembangan


### 8.2 Pembelajaran Teknis
Proyek ini mendemonstrasikan:
- **Advanced C++**: Modern C++ practices dan STL usage
- **Design Patterns**: Practical implementation dalam game development
- **Game Architecture**: Scalable dan maintainable code structure
- **Resource Management**: Proper handling of assets dan memory
- **UI Programming**: Event-driven interface development

### 8.3 Potensi Pengembangan
Future enhancements yang dapat diimplementasikan:
- **Save/Load System**: Game state persistence
- **Shop System**: Item trading dan equipment
- **Boss Battles**: Unique encounters dengan special mechanic
- **Audio Effects**: Sound feedback untuk actions
