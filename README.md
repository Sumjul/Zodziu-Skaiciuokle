# Pasikartojančių žodžių skaičiuoklė ir nuorodų ieškoklė

## > **Programos paleidimas naudojant CmakeLists** <

## ✅ Reikalavimai

Įsitikinkite, kad turite įdiegtus šiuos įrankius savo sistemoje:

- **C++ kompiliatorius** (pvz., GCC arba MSVC)
- **CMake** (bent 3.25 versija)

> **Pastaba:** Git nebūtinas, jei jau turite projekto failus.

---

## 🔧 Projekto paruošimas ir paleidimas

### 1. Projekto failų paruošimas

Jeigu dar neturite projekto aplanke, galite jį atsisiųsti arba nusiklonuoti iš saugyklos:

```sh
git clone <projekto_git_nuoroda>
cd <projekto_katalogas>
```

> **Pastaba:** Jei norite programuoti ar paleisti programą, įsitikinkite, kad teksto failas yra tinkamoje vietoje (pvz., `src/tekstas.txt`) arba įtrauktas į build katalogą naudojant `CMakeLists.txt` ar kitus automatinius kopijavimo būdus.

### 2. Paleidimas naudojant run.bat (Windows)

Norėdami automatiškai sukompiliuoti ir paleisti programą, tiesiog dukart spustelėkite failą:

```sh
run.bat
```

Šis failas:

- automatiškai sukuria `build/` katalogą (jeigu jo dar nėra),
- sugeneruoja ir sukompiliuoja projektą naudojant CMake.

---

### Alternatyvus rankinis paleidimas (jei reikia)

Jei norite viską daryti per komandų eilutę:

```sh
cmake -B build -S .
cmake --build build
build\Zodziu_Skaiciuokle.exe
```

---
---

## **> 📑 Programos naudojimosi instrukcija <**

Ši programa skirta analizuoti tekstą, rasti pasikartojančius žodžius ir nuorodas.

## Kaip veikia programa?

- Paleidus programą, ji paima tekstą iš nurodyto failo.
- Iš teksto programa randa **visus pasikartojančius žodžius**.
- Kiekvienas rastas žodis išvedamas į rezultatų failą `pasikartojimai.txt`, po vieną žodį kiekvienoje eilutėje.
- Kiekvienoje eilutėje žodis pateikiamas tokiu formatu:

```sh
žodis --- | pasikartojimų skaičius | (eilutės numeriai, kur žodis pasikartojo)
```

- Be žodžių, programa taip pat **ieško visas nuorodas tekste**: sutrumpintus ir nesutrumpintus URL adresus.
- Rasti URL taip pat išvedami į atskirą rezultatų failą `nuorodos.txt`, kad būtų galima juos peržiūrėti.
