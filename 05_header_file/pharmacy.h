#pragma once
#include <iostream>


bool barcodeExists(const std::string& fileName, const std::string& barcode);
// TODO: ilk alan barcode ile eşleşiyor mu?


 
void addMedicine(const std::string& fileName,
                 const std::string& barcode, const std::string& name,
                 int stock, double price, const std::string& expiry);
// TODO: barcodeExists kontrolü
// TODO: barcode,name,stock,price,expiry formatında append

 
void listMedicines(const std::string& fileName, const std::string& today);
// TODO: her satırı oku
// TODO: expiry < today ise yanına "[SKT GECMIS]" ekle

 
void sellMedicine(const std::string& fileName,
                  const std::string& barcode, int qty,
                  const std::string& today);
// TODO: temp dosya
// TODO: barkod eşleşirse:
//   - SKT geçmişse hata ver ve return (temp dosyayı kapatıp orijinali koru)
//   - Stok < qty ise hata ver ve return
//   - Stok -= qty yaz
// TODO: remove + rename

 
void checkExpired(const std::string& fileName, const std::string& today);
// TODO: expiry < today olanları listele

 
void lowStock(const std::string& fileName, int threshold);
// TODO: stok < threshold olanları listele

 
void updatePrice(const std::string& fileName,
                 const std::string& barcode, double newPrice);
// TODO: temp dosya, barkod eşleşirse fiyatı güncelle
// TODO: remove + rename

 