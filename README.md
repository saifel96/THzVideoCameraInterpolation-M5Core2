# Hinweis: Die englische Version dieser Dokumentation finden Sie weiter unten. #

# Note: The English version of this documentation is available below. # 

## 1. Einleitung: ##

Die heutigen Terahertz-Technologien versprechen ein rasches Wachstum in den neuen Märkten wie Medizin- und Sicherheitstechnik, zerstörungsfreie Prüfung, Qualitätskontrolle und Gesundheitsvorsorge. Jedoch ist die Geschwindigkeit, mit der neue Märkte entstehen noch langsam, weil verfügbare Technologien hohen Kosten und eine niedrige Ebene der Integration aufweisen, die ihren Masseneinsatz wesentlich einschränken.

Im Lehrstuhl für Hochfrequenzsysteme in der Kommunikationstechnik beschäftigten wir uns intensiv mit der eingebetteten Bildverarbeitung von Terahertz (THz) Video-Kameras. Konkret untersuchten wir die bereits entwickelte und hergestellte THz-Kamera T-LITE M5STICK Plus der Firma M5Stack Technology Co., Ltd., die mit einem THz-Sensor des Typs MLX90640 ausgestattet ist.

Ziel unserer Arbeit war es, die Bilddaten der Kamera zu interpolieren, die von einer Auflösung von 32x24 Pixeln auf eine höhere Auflösung von 135x240 Pixeln skaliert werden sollten. Dies ermöglichte den Vergleich verschiedener Interpolationsmethoden auf zwei unterschiedlichen Plattformen, dem M5Core2 (240x320 Pixel) und dem M5Stick Plus.

Darüber hinaus bestand eine zentrale Aufgabe darin, den Interpolationsalgorithmus aus dem Hauptquellcode des Produkts zu isolieren und separat auf beiden Geräten zu implementieren. Abschließend untersuchten wir die Bildwiederholrate (FPS) für verschiedene Algorithmen auf beiden Plattformen, um die Effizienz und Leistungsfähigkeit der Implementierungen zu vergleichen.

## 2.	 Hardware: ##

Im rahmen diesem Praktikum haben wir uns mit Zwei Hardware Beschäftigt: 

- M5STACK CORE2:

![image](https://github.com/user-attachments/assets/5a559da6-89d2-46b9-ae68-ed1d4925ec2b)

- T-LITE M5StickC-PLUS:

![image](https://github.com/user-attachments/assets/fb91fab4-0dec-4566-96d0-fc108368f909)

- M5StickC Plus: 

![image](https://github.com/user-attachments/assets/c28abca7-2350-423b-8cf9-62ed635e43c5)

- Thermal Hat MLX90640:

![image](https://github.com/user-attachments/assets/738464eb-2f33-4ad0-ab95-68ae6023549e)


## 3. InterpolationAlgorithmen: ##
   
Anstatt direkt mit den Daten des THz-Sensors zu arbeiten, haben wir zunächst mit einem einfachen Bild begonnen. Dieses Bild hatte eine Auflösung von 32x24 Pixeln, und wir haben es in ein Array umgewandelt, um es dann zu interpolieren.
Unser Ziel war es, das Bild von 32x24 Pixeln auf 135x240 Pixel zu vergrößern. Dafür haben wir verschiedene Interpolationsmethoden verwendet, darunter:

- Bilineare Interpolation.
- Bicubische Interpolation.
- Nearest-Neighbour-Interpolation.
- Isolierte Interpolationsmethode aus dem Original-Quellcode der T-LITE M5StickC Plus. aus ("https://github.com/m5stack/M5StickC-Plus-TLite-FW/blob/main/src/main.cpp")

## 4.	Implementierung von Interpolationsalgorithmen:  ##

Wir haben verschiedene Interpolationsverfahren implementiert und diese anschließend in die Geräte M5Core2 und M5StickC Plus integriert. Dabei sind wir jedoch auf einige Herausforderungen gestoßen.

-	Umwandlung und Inversion von Bitmap-Daten:

Wir haben das Bild im „Bitmap“-Format, wobei die erste Zeile tatsächlich die letzte im Daten-Array von Bytes ist. Daher müssen wir die Zeilen invertieren. Zusätzlich speichert die Bitmap jeder Pixel in 3 Bytes (B, G und R) im RGB888-Format. Um diese Daten in ein 24-Bit-Farbformat (RGB565) umzuwandeln, verwenden wir eine Funktion namens void(rgb888_to_rgb565), die beide Aufgaben ausführt.

-	Das Speicherproblem:

Zunächst haben wir beim Konvertieren von RGB888 nach RGB565 Speicher für das gesamte Bild zugewiesen, was jedoch nicht möglich war, da der verfügbare Speicher nicht ausreichte. Daher bestand die Lösung darin, nur eine einzelne Zeile zuzuweisen, diese anzuzeigen und dann zur nächsten Zeile überzugehen, um sie zu konvertieren und ebenfalls anzuzeigen, und so weiter.

Abschließend haben wir die Leistung der Algorithmen auf diesen Geräten getestet, indem wir die Bildwiederholrate (FPS) und die Effizienz der Implementierungen miteinander verglichen haben.

## 5.	Data Visualisieren und Ergebnisse:  ##

   Um einen fairen Vergleich zwischen den beiden Hardwareplattformen, M5Core2 und M5StickC Plus, zu ermöglichen, haben wir unsere Interpolationsalgorithmen auf beiden Geräten getestet. Dabei verwendeten wir eine Bildgröße von 135x240 Pixeln für alle Verfahren. Die folgende Tabelle zeigt die Unterschiede in der Bildwiederholrate (FPS) für die verschiedenen Algorithmen auf den beiden Geräten

![image](https://github.com/user-attachments/assets/6cc1ef01-7788-4ece-8951-33d37197a04b)

![image](https://github.com/user-attachments/assets/e104c755-1488-417f-953d-19b54b8d8176)


Diese Ergebnisse zeigen deutliche Unterschiede in der Performance zwischen den beiden Geräten. Während M5StickC Plus in den meisten Fällen eine höhere Bildwiederholrate erreicht, insbesondere bei der bilinearen und Nearest-Neighbour-Interpolation, zeigt die bicubische Interpolation auf beiden Geräten ähnliche und niedrigere Werte. Die aus dem Original-Quellcode isolierte Interpolation liefert ebenfalls eine signifikant bessere Leistung auf dem M5StickC Plus im Vergleich zum M5Core2.

## 6.	Analyse der Leistungsunterschiede zwischen M5Core2 und M5StickC Plus:  ##

   
Obwohl wir die gleiche Software auf beiden Geräten, dem M5Core2 und dem M5StickC Plus, verwendet haben, gibt es einen wesentlichen Unterschied in der Leistung. Dieser Unterschied ist nicht auf die Software zurückzuführen, sondern lässt uns über andere mögliche Ursachen nachdenken, die hardwareabhängig sind.
Die Unterschiede in der Leistung (FPS) zwischen den beiden Geräten, M5Core2 und M5StickC Plus, können aus mehreren Gründen entstehen:

- Prozessorarchitektur und Unterschiede zwischen den ESP32-Chips:
  Beide Geräte verwenden den ESP32-Chip, aber es gibt subtile Unterschiede zwischen den Varianten. Der ESP32 D0WDQ6-V3 im M5Core2 und der ESP32-PICO im M5StickC Plus sind zwar ähnliche Chips, aber der ESP32-PICO ist eine kompaktere Version, die alle notwendigen Komponenten (wie Flash-Speicher, Quarz und Antenne) auf einem einzigen Modul integriert. Dies kann den Stromverbrauch und die Effizienz verbessern, was zu einer besseren Leistung bei Interpolationsaufgaben führen könnte.
- Integriertes Crystal:
  Der ESP32-PICO enthält einen integrierten Quarzkristall, der eine präzise Taktfrequenz bereitstellt. Hier sind einige mögliche Auswirkungen auf die Leistung:
  Ein integriertes Crystal bedeutet, dass die Taktung des Prozessors genau abgestimmt und stabil ist. Es gibt weniger externe Faktoren, die die Taktfrequenz beeinflussen können (wie elektrische Störungen oder Temperaturschwankungen). Diese genaue Taktung könnte dazu führen, dass der ESP32-PICO konstant mit der maximal möglichen Geschwindigkeit arbeitet, was eine höhere Effizienz und bessere Leistung bei Prozessen wie der Bildverarbeitung und Interpolation ermöglicht.
- Integrierter 4 MB Flash-Speicher:
  Der integrierte 4 MB Flash-Speicher des ESP32-PICO kann ebenfalls die Leistung bei Bildverarbeitungsaufgaben erheblich beeinflussen. Hier sind die Gründe, warum dies der Fall sein könnte:
  Da der Flash-Speicher direkt im ESP32-PICO integriert ist, kann die CPU schneller auf den Speicher zugreifen. Im Vergleich zu einem externen Flash-Speicher (wie möglicherweise beim M5Core2), bei dem zusätzliche Latenzen beim Speicherzugriff auftreten können, arbeitet der ESP32-PICO effizienter, da weniger Zeit für den Datenaustausch zwischen CPU und Speicher benötigt wird. Dies ist besonders wichtig, wenn große Datenmengen wie Bilddaten verarbeitet werden müssen.
- Weniger externe Komponenten:
  Da der ESP32-PICO viele seiner Komponenten, einschließlich Crystal und Flash-Speicher, intern integriert hat, gibt es weniger externe Verbindungen und damit weniger Signalverluste oder Latenzen. Externe Verbindungen, wie sie im M5Core2 möglicherweise existieren, könnten die Verarbeitungsgeschwindigkeit beeinträchtigen. Je weniger externe Komponenten ein Gerät hat, desto direkter und schneller kann die CPU auf wichtige Ressourcen wie den Flash-Speicher zugreifen.


 ## 7.	Zusammenfassung:  ##

   Im Rahmen dieses Projekts haben wir uns mit der Bildverarbeitung und Interpolation von Thermalkameradaten auf zwei verschiedenen Geräten, dem M5Core2 und dem M5StickC Plus, beschäftigt. Ziel war es, Bilddaten einer THz-Kamera von einer Auflösung von 32x24 Pixeln auf 135x240 Pixel zu interpolieren und verschiedene Interpolationsmethoden zu testen. Zu den angewandten Algorithmen gehörten lineare, bilineare, bicubische und Nearest-Neighbour-Interpolation sowie eine spezielle Interpolation, die wir aus dem Quellcode des M5StickC Plus isolieren konnten.

Um die Effizienz dieser Algorithmen zu evaluieren, haben wir sie auf beiden Geräten implementiert und getestet. Dabei wurden die FPS (Frames per Second) als Leistungskennzahl herangezogen, um die Geschwindigkeit der Bildverarbeitung zu vergleichen. Die Ergebnisse zeigten signifikante Unterschiede zwischen den beiden Geräten, wobei der M5StickC Plus in den meisten Fällen höhere FPS erzielte als der M5Core2.

Die Unterschiede in der Leistung lassen sich vor allem auf hardwaretechnische Faktoren zurückführen. Obwohl auf beiden Geräten die gleiche Software ausgeführt wurde, spielten die Unterschiede in der Prozessorarchitektur, der Taktfrequenzstabilität durch integrierte Quarze und die Effizienz des integrierten Flash-Speichers des ESP32-PICO-D4 eine entscheidende Rolle für die bessere Performance des M5StickC Plus.

Insgesamt konnte durch dieses Projekt gezeigt werden, wie wichtig die Hardwarekonfiguration für die Performance von Bildverarbeitungsalgorithmen ist. Die Ergebnisse liefern wertvolle Erkenntnisse für die weitere Optimierung von Bildverarbeitungsprozessen auf Embedded-Systemen, insbesondere im Hinblick auf Echtzeit-Anwendungen wie die Thz-Video Camera.

Für den vollständigen Bericht, finden Sie ihn unter folgendem Link : https://github.com/saifel96/THzVideoCameraInterpolation-M5Core2/blob/master/TeamPraktikum%20-%20Eingebettete%20Bildinterpolation%20von%20THz%20Video-kamera.pdf


##

## English Version ##



## 1. Introduction:  ##
Today, terahertz technologies promise rapid growth in emerging markets such as medical and security technology, non-destructive testing, quality control, and healthcare. However, the pace at which these new markets are developing remains slow, primarily due to the high costs and low integration levels of available technologies, which significantly limit their widespread adoption.

At the Chair of High-Frequency Systems in Communication Technology, we focused on the embedded image processing of terahertz (THz) video cameras. Specifically, we studied the already developed and manufactured T-LITE M5STICK Plus camera from M5Stack Technology Co., Ltd., which is equipped with a THz sensor of the MLX90640 type.

The goal of our work was to interpolate the image data from the camera, scaling the resolution from 32x24 pixels to a higher resolution of 135x240 pixels. This enabled us to compare various interpolation methods on two different platforms: the M5Core2 (240x320 pixels) and the M5Stick Plus.

Additionally, a key task was to isolate the interpolation algorithm from the product's main source code and implement it separately on both devices. Finally, we examined the frame rate (FPS) for various algorithms on both platforms to compare the efficiency and performance of the implementations.

## 2. Hardware:  ##
In this project, we worked with two main hardware devices:

- M5STACK CORE2:

![image](https://github.com/user-attachments/assets/5a559da6-89d2-46b9-ae68-ed1d4925ec2b)

- T-LITE M5StickC-PLUS:

![image](https://github.com/user-attachments/assets/fb91fab4-0dec-4566-96d0-fc108368f909)

- M5StickC Plus: 

![image](https://github.com/user-attachments/assets/c28abca7-2350-423b-8cf9-62ed635e43c5)

- Thermal Hat MLX90640:

![image](https://github.com/user-attachments/assets/738464eb-2f33-4ad0-ab95-68ae6023549e)


## 3. Interpolation Algorithms:  ##
Instead of working directly with the THz sensor data, we initially began with a simple image. This image had a resolution of 32x24 pixels, which we converted into an array to interpolate.

Our goal was to upscale the image from 32x24 pixels to 135x240 pixels. To achieve this, we used various interpolation methods, including:

- Bilinear interpolation.
- Bicubic interpolation.
- Nearest-neighbor interpolation.
- An isolated interpolation method from the original T-LITE M5StickC Plus source code (from "https://github.com/m5stack/M5StickC-Plus-TLite-FW/blob/main/src/main.cpp").

## 4. Implementation of Interpolation Algorithms:  ##
We implemented various interpolation methods and then integrated them into the M5Core2 and M5StickC Plus devices. However, we faced several challenges:

- Conversion and inversion of bitmap data: 
We worked with images in the "bitmap" format, where the first line in the image is actually the last in the byte array. Thus, we had to invert the lines. Additionally, each pixel in the bitmap is stored in 3 bytes (B, G, and R) in the RGB888 format. To convert this data into a 24-bit color format (RGB565), we used a function called void(rgb888_to_rgb565), which performed both tasks.

- Memory problem:
  Initially, we allocated memory for the entire image when converting from RGB888 to RGB565, but this was not feasible due to insufficient memory. The solution was to allocate memory for only one line at a time, display it, then move to the next line, convert it, and display it, and so on.

Finally, we tested the performance of the algorithms on both devices by comparing the frame rate (FPS) and the efficiency of the implementations.

## 5. Data Visualization and Results:  ##
To ensure a fair comparison between the two hardware platforms, M5Core2 and M5StickC Plus, we tested our interpolation algorithms on both devices, using a 135x240 pixel image for all methods. The following table shows the differences in frame rate (FPS) for the various algorithms on both devices:


![image](https://github.com/user-attachments/assets/6cc1ef01-7788-4ece-8951-33d37197a04b)

![image](https://github.com/user-attachments/assets/e104c755-1488-417f-953d-19b54b8d8176)



These results show significant differences in performance between the two devices. While the M5StickC Plus achieves a higher frame rate in most cases, particularly with bilinear and nearest-neighbor interpolation, bicubic interpolation shows similar and lower values on both devices. The isolated interpolation method from the original source code also delivers significantly better performance on the M5StickC Plus compared to the M5Core2.

## 6. Performance Analysis between M5Core2 and M5StickC Plus:  ##
Despite using the same software on both the M5Core2 and M5StickC Plus, there is a significant difference in performance. This difference is not due to the software but points to other potential hardware-related causes.

The performance differences (FPS) between the two devices, M5Core2 and M5StickC Plus, can be attributed to several factors:

- Processor architecture and differences between ESP32 chips: Both devices use the ESP32 chip, but there are subtle differences between the variants. The ESP32 D0WDQ6-V3 in the M5Core2 and the ESP32-PICO in the M5StickC Plus are similar chips, but the ESP32-PICO is a more compact version that integrates essential components (such as flash memory, crystal, and antenna) into a single module. This could improve power efficiency and lead to better performance in interpolation tasks.

- Integrated Crystal: The ESP32-PICO includes an integrated crystal, providing precise clock frequency. This results in a more stable clock, potentially allowing the ESP32-PICO to consistently operate at maximum speed, improving efficiency and performance in tasks such as image processing and interpolation.

- Integrated 4 MB Flash Memory: The integrated 4 MB flash memory of the ESP32-PICO may also significantly impact performance in image processing tasks. Direct access to flash memory allows for faster CPU operations, which is particularly important for processing large datasets like image data.

- Fewer external components: The ESP32-PICO integrates many components internally, reducing external connections and potential signal loss or latency. The M5Core2, with potentially more external components, might experience slower processing speeds due to these factors.

## 7. Conclusion:  ##
In this project, we explored image processing and interpolation of thermal camera data on two different devices, the M5Core2 and the M5StickC Plus. Our goal was to interpolate the image data from a THz camera from a resolution of 32x24 pixels to 135x240 pixels, using various interpolation methods. These methods included linear, bilinear, bicubic, and nearest-neighbor interpolation, as well as a specialized interpolation method isolated from the M5StickC Plus source code.

We implemented and tested these algorithms on both devices, using FPS (frames per second) as a metric for comparing image processing speed. The results showed significant performance differences between the two devices, with the M5StickC Plus achieving higher FPS in most cases compared to the M5Core2.

These performance differences can largely be attributed to hardware factors, including processor architecture, clock stability due to integrated crystals, and the efficiency of the ESP32-PICO-D4's integrated flash memory.

Overall, this project demonstrated the importance of hardware configuration in the performance of image processing algorithms. The results provide valuable insights for further optimization of image processing on embedded systems, particularly for real-time applications such as the THz video camera.

For the full report, you can find it at the following link: https://github.com/saifel96/THzVideoCameraInterpolation-M5Core2/blob/master/TeamPraktikum%20-%20Eingebettete%20Bildinterpolation%20von%20THz%20Video-kamera.pdf.
