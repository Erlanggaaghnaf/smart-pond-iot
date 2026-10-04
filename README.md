# Smart Pond: Pemantau Suhu dan pH Air Kolam Ikan

Simulasi sistem **Smart Pond** berbasis **Arduino Mega 2560** pada simulator [Wokwi](https://wokwi.com/projects/476795099737101313). Sistem membaca suhu dan pH air kolam ikan, menampilkan hasilnya pada LCD dan Serial Monitor, memberi peringatan lewat LED dan buzzer, serta menyalakan pompa dan aerator secara otomatis ketika kondisi air tidak normal.

Proyek ini dibuat untuk **Praktikum IoT** sebagai simulasi penerapan IoT sederhana (penginderaan, pengolahan data, dan pengendalian).

## Fitur

- Membaca suhu air dengan sensor **DS18B20**.
- Membaca nilai pH dengan **potensiometer** sebagai simulasi sensor pH (nilai ADC 0 sampai 1023 dipetakan ke pH 0 sampai 14).
- Menentukan kondisi air: normal, pH terlalu asam, pH terlalu basa, suhu rendah, atau suhu tinggi.
- Menampilkan nilai pH, suhu, dan kondisi air pada **LCD 16x2 I2C** dan **Serial Monitor**.
- Indikator **LED hijau** (normal) dan **LED merah** (tidak normal), serta **buzzer** sebagai peringatan.
- Mengendalikan **pompa** dan **aerator** melalui dua modul relay.
- Menampilkan identitas pembuat pada LCD dan Serial Monitor saat sistem dinyalakan.

## Batas Kondisi Normal

| Parameter | Batas Normal |
|-----------|--------------|
| pH        | 6,5 sampai 8,0 |
| Suhu      | 25 °C sampai kurang dari 30 °C |

## Cara Kerja Sistem

| Kondisi | LCD (baris 2) | LED | Buzzer | Pompa dan Aerator |
|---------|---------------|-----|--------|-------------------|
| Normal | `AIR: NORMAL` | Hijau menyala | Mati | OFF |
| pH terlalu asam (pH < 6,5) | `PH: ASAM!` | Merah menyala | Berbunyi | ON |
| pH terlalu basa (pH > 8,0) | `PH: BASA!` | Merah menyala | Berbunyi | ON |
| Suhu rendah (< 25 °C) | `SUHU RENDAH` | Merah menyala | Berbunyi | ON |
| Suhu tinggi (>= 30 °C) | `SUHU TINGGI` | Merah menyala | Berbunyi | ON |

Pemeriksaan dilakukan berurutan: pH asam, pH basa, suhu rendah, lalu suhu tinggi. Jika semuanya aman, kondisi dianggap normal. Data dibaca dan diperbarui setiap 1 detik.

## Komponen

- Arduino Mega 2560
- Sensor suhu DS18B20 dan resistor 4,7 kΩ (pull-up)
- Potensiometer (simulasi sensor pH)
- LCD 16x2 dengan modul I2C (alamat `0x27`)
- 2 modul relay (pompa dan aerator)
- 2 LED (hijau dan merah) dan 2 resistor 220 Ω
- Buzzer
- Breadboard dan kabel jumper

## Perkabelan

| Komponen | Pin Komponen | Pin Arduino Mega |
|----------|--------------|------------------|
| Potensiometer | SIG | A0 |
| Sensor DS18B20 | DQ | 7 (resistor pull-up 4,7 kΩ ke 5V) |
| LCD 16x2 I2C | SDA, SCL | 20, 21 |
| Relay 1 (pompa) | IN | 8 |
| Relay 2 (aerator) | IN | 9 |
| LED hijau | Anoda (via resistor 220 Ω) | 10 |
| LED merah | Anoda (via resistor 220 Ω) | 11 |
| Buzzer | Pin 2 | 12 |
| Semua komponen | VCC dan GND | 5V dan GND |

## Struktur File

```
.
├── sketch.ino          # Kode program Arduino
├── diagram.json        # Rangkaian pada Wokwi
├── libraries.txt       # Daftar pustaka yang digunakan
├── wokwi-project.txt   # Tautan proyek Wokwi
└── README.md
```

## Pustaka yang Digunakan

- `OneWire`
- `DallasTemperature`
- `LiquidCrystal I2C`

## Cara Menjalankan

**Lewat Wokwi (online)**

1. Buka [proyek di Wokwi](https://wokwi.com/projects/476795099737101313).
2. Klik tombol **Start the simulation**.
3. Putar potensiometer untuk mengubah nilai pH.
4. Klik sensor DS18B20 lalu geser slider suhu untuk mengubah suhu air.
5. Amati LCD, LED, buzzer, relay, dan Serial Monitor.

**Dari repository ini**

1. Buat proyek baru Arduino Mega di Wokwi.
2. Salin isi `sketch.ino` dan `diagram.json` ke proyek tersebut.
3. Tambahkan pustaka yang tercantum pada `libraries.txt`, lalu jalankan simulasi.

<img width="908" height="671" alt="image" src="https://github.com/user-attachments/assets/fc81ce28-f539-4315-8594-c12b205c28ce" />
<img width="904" height="665" alt="image" src="https://github.com/user-attachments/assets/eaa938bc-bed9-42a5-9105-e044ed832f65" />
<img width="903" height="664" alt="image" src="https://github.com/user-attachments/assets/84492ee1-eaa6-459c-9d79-78556003b3f2" />
<img width="903" height="669" alt="image" src="https://github.com/user-attachments/assets/d66039c9-c516-43e4-93ee-79a425fe3b57" />
<img width="906" height="665" alt="image" src="https://github.com/user-attachments/assets/f3297013-057e-48b5-9042-5a78954714cb" />
<img width="903" height="640" alt="image" src="https://github.com/user-attachments/assets/73a31f39-0676-4175-b127-f46c057fd11f" />
