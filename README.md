**Final Project Pemrograman Lanjut**

---

## DAFTAR ISI
1. Pendahuluan
2. Deskripsi Proyek
3. Fitur Utama
4. Arsitektur Sistem
5. Implementasi Teknis
6. Struktur File
7. Gameplay dan Mekanik
8. Teknologi yang Digunakan
9. Kesimpulan

---

## 1. PENDAHULUAN

**Exploration 22** adalah sebuah game RPG (Role-Playing Game) berbasis turn-based combat yang dikembangkan menggunakan C++ dan library SFML (Simple and Fast Multimedia Library). Game ini menggabungkan elemen eksplorasi dungeon, pertarungan strategis, dan pengembangan karakter dalam sebuah pengalaman gaming yang komprehensif.

### Tujuan Proyek
- Implementasi konsep Object-Oriented Programming dalam pengembangan game
- Penerapan design patterns (State Pattern, Factory Pattern, Observer Pattern)
- Demonstrasi kemampuan manajemen memori dengan smart pointers
- Penggunaan library grafis SFML untuk rendering dan audio

---

## 2. DESKRIPSI PROYEK

**Exploration 22** adalah game petualangan di mana pemain memimpin sebuah party beranggotakan hingga 3 karakter untuk menjelajahi 5 lantai dungeon yang berbeda. Setiap lantai memiliki 5 langkah dengan berbagai jenis node yang menawarkan tantangan dan reward yang berbeda.

### Konsep Dasar
- **Genre**: Turn-based RPG dengan elemen eksplorasi
- **Platform**: Desktop (Windows/Linux)
- **Target Audience**: Penggemar game strategi dan RPG
- **Durasi Gameplay**: 30-60 menit per playthrough

---

## 3. FITUR UTAMA

### 3.1 Sistem Karakter
- **4 Karakter Unik**: Arthesa, Ahmed, Perkia, dan Hamilla
- **Sistem Stats**: HP, ATK, DEF, MAG, RES dengan progression dinamis
- **Tipe Entity**: MORTAL, ETHEREAL, CONSTRUCT (rock-paper-scissors system)
- **Skill System**: Setiap karakter memiliki 4 kemampuan unik dengan AP cost berbeda

### 3.2 Sistem Pertarungan
- **Turn-based Combat**: Pemain dan musuh bergantian menyerang
- **AP System**: 6 Action Points per turn untuk strategi resource management
- **Target Selection**: Pemilihan target yang fleksibel
- **Damage Calculation**: Kompleks dengan berbagai modifier

### 3.3 Sistem Eksplorasi
- **5 Lantai Dungeon**: Setiap lantai memiliki struktur unik
- **Node Types**: BATTLE, EVENT, SHOP, BOSS
- **Linear Progression**: Single → Branch → Single → Branch → Boss
- **Visual Navigation**: Interface grafis untuk navigasi

### 3.4 Sistem Event
- **5 Random Events**: Scenario acak dengan pilihan bermakna
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
- Separation of concerns untuk setiap gameplay phase

#### Factory Pattern
```cpp
const std::vector<std::function<std::unique_ptr<Enemy>()>> ENEMY_TEMPLATES = {
    makeGoblin, makeSkeleton, makeWitch, makeWizard, makeFireWorm
};
```
**Implementasi**:
- Dynamic enemy creation
- Scalable enemy system
- Lambda-based attack behaviors

#### Observer Pattern
- Party management system
- Real-time HP/status updates
- Event-driven UI updates

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
- **Smart Pointers**: Extensive use of `std::unique_ptr` dan `std::shared_ptr`
- **RAII Principle**: Automatic resource management
- **No Memory Leaks**: Proper destructor implementation

### 5.2 Data Structures
```cpp
// Party management
std::vector<std::unique_ptr<Character>> members;

// Floor generation
std::vector<std::vector<std::unique_ptr<Node>>> steps;

// Enemy groups
std::vector<std::unique_ptr<Enemy>> enemies;
```

### 5.3 Error Handling
- Exception handling untuk file loading
- Defensive programming practices
- Graceful error recovery

### 5.4 Performance Optimization
- Efficient sprite rendering
- Minimized dynamic allocations
- Optimized game loop

---

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
├── AI Target Selection
├── Random Attack Choice
└── Damage Application
```

### 7.3 Character Progression
- **Event-based Upgrades**: Permanent stat increases melalui events
- **No Traditional Leveling**: Progression melalui pilihan strategis
- **Risk vs Reward**: Setiap pilihan memiliki trade-off

### 7.4 Enemy System
- **5 Enemy Types**: Goblin, Skeleton, Witch, Wizard, Fire Worm
- **Lambda-based Attacks**: Fleksibilitas dalam behavior definition
- **Randomized Encounters**: 2-3 enemies per battle node

---

## 8. TEKNOLOGI YANG DIGUNAKAN

### 8.1 Programming Language
- **C++14**: Modern C++ features
- **STL**: Standard Template Library untuk containers
- **Smart Pointers**: Memory management

### 8.2 Libraries
- **SFML 2.5+**: Graphics, Audio, Window management
  - `sf::Graphics`: Rendering sprites dan text
  - `sf::Audio`: Background music dan sound effects
  - `sf::Window`: Event handling dan window management

### 8.3 Development Tools
- **GCC**: Compiler dengan C++14 support
- **Makefile**: Build automation
- **Git**: Version control

### 8.4 Assets
- **Sprites**: Custom pixel art untuk characters dan enemies
- **Fonts**: PixelOperator.ttf, OldEnglishGothicPixel.ttf
- **Music**: Background theme "Horsemen Approach"
- **Backgrounds**: Scene-specific artwork

---

## 9. FITUR TEKNIS LANJUTAN

### 9.1 Animation System
```cpp
// Sprite animation dengan frame cycling
sf::Clock animationClock;
currentFrame = (currentFrame + 1) % maxFrames;
characterSprites[i].setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
```

### 9.2 Random Generation
```cpp
// Floor generation dengan controlled randomness
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(0, 2);
```

### 9.3 Event System
- **Modular Events**: Easy addition of new scenarios
- **Choice Consequences**: Immediate and long-term effects
- **Upgrade System**: Multiple stat modification types

### 9.4 UI/UX Features
- **Keyboard Navigation**: Intuitive controls
- **Visual Feedback**: Color-coded selection dan status
- **State Persistence**: Game state maintained across transitions

---

## 10. KESIMPULAN

### 10.1 Pencapaian Proyek
**Exploration 22** berhasil mengimplementasikan:
- ✅ Complete RPG game loop
- ✅ Object-oriented design dengan proper inheritance
- ✅ Memory-safe programming dengan smart pointers
- ✅ Modular architecture untuk easy expansion
- ✅ Rich gameplay dengan multiple systems
- ✅ Professional-grade error handling

### 10.2 Pembelajaran Teknis
Proyek ini mendemonstrasikan:
- **Advanced C++**: Modern C++ practices dan STL usage
- **Design Patterns**: Practical implementation dalam game development
- **Game Architecture**: Scalable dan maintainable code structure
- **Resource Management**: Proper handling of assets dan memory
- **UI Programming**: Event-driven interface development

### 10.3 Potensi Pengembangan
Future enhancements yang dapat diimplementasikan:
- **Save/Load System**: Game state persistence
- **Shop System**: Item trading dan equipment
- **Boss Battles**: Unique encounters dengan special mechanics
- **Audio Effects**: Sound feedback untuk actions
- **Multiplayer**: Network-based party cooperation

### 10.4 Nilai Edukatif
Proyek ini mencakup konsep-konsep penting dalam:
- **Software Engineering**: Clean code, modularity, testing
- **Game Development**: Game loops, state machines, asset management
- **Object-Oriented Programming**: Inheritance, polymorphism, encapsulation
- **C++ Programming**: Modern syntax, memory management, STL

---

**Total Lines of Code**: ~2000+ LOC  
**Development Time**: Semester duration  
**File Count**: 30+ source files  
**Asset Count**: 20+ sprites, backgrounds, dan audio files  

Proyek **Exploration 22** berhasil menciptakan pengalaman gaming yang lengkap sambil mendemonstrasikan penerapan konsep-konsep advanced programming dalam konteks yang praktis dan menarik.