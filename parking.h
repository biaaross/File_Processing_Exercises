#pragma once

#include <string>
 
int toMinutes(const std::string& time);
// TODO: "HH:MM" formatını dakikaya çevir
// İPUCU: "08:30" → saat=8, dakika=30 → 8*60+30 = 510


bool isInside(const std::string& fileName, const std::string& plate);
// TODO: dosyayı oku, CikisSaati=="-" olan aynı Plaka var mı?


void enterParking(const std::string& fileName,
                  const std::string& plate, const std::string& spot,
                  const std::string& entryTime);
// TODO: isInside kontrolü, zaten içerideyse hata ver ve return
// TODO: plate,spot,entryTime,-,0 formatında append
// TODO: "[OK] ... girdi → Park yeri: ..." yazdır



void exitParking(const std::string& fileName,
                 const std::string& plate, const std::string& exitTime);
// TODO: temp dosya
// TODO: Plaka eşleşiyor ve CikisSaati=="-" olan satırı bul
//       bulunamazsa "[HATA] Plaka bulunamadi" yaz
// TODO: CikisSaati=exitTime yap
// TODO: Ucret = (exitDakika - entryDakika) * 1.5
// TODO: remove + rename
 


void listParking(const std::string& fileName);
// TODO: tüm kayıtları oku
// TODO: CikisSaati=="-" ise "ICERIDE", değilse ücret göster

double dailyRevenue(const std::string& fileName);
// TODO: Ucret alanı > 0 olanları topla, döndür