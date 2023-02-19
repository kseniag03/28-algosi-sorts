##  АиСД 2023 КДЗ №1

### 1. Ганина Ксения Андреевна 212 (тг для вопросов: @kgnn47)
### 2. CLion & IDLE python & MS Excel
### 3. Сделано: 28 удар... 13 сортировок, замеры времени, функция проверки упорядоченности элементов массива, генерация массивов, вывод исходного массива в input.txt, полученного в output.txt, сохранение результатов замеров в файл .cvs, счётчик эл-х операций, графики
### 4. Не сделано: транпонирование контейнера для вывода данных по отдельным сортировкам (выполнялось лапками в excel...)
### 5. Задание: https://edu.hse.ru/pluginfile.php/2326684/mod_resource/content/1/КДЗ_1.pdf
________________________

## 3. Анализ по массивам <br>

### 3.1. 0-5
![image](cmake-build-debug/data/01data.png)
![image](cmake-build-debug/data/05data.png)
![image](cmake-build-debug/data/09data.png)
![image](cmake-build-debug/data/013data.png)

### 3.2. 0-4000
![image](cmake-build-debug/data/02data.png)
![image](cmake-build-debug/data/06data.png)
![image](cmake-build-debug/data/010data.png)
![image](cmake-build-debug/data/014data.png)

### 3.3. почти-отсортированный
![image](cmake-build-debug/data/03data.png)
![image](cmake-build-debug/data/07data.png)
![image](cmake-build-debug/data/011data.png)
![image](cmake-build-debug/data/015data.png)

### 3.4. отсортированный-по-убыванию
![image](cmake-build-debug/data/04data.png)
![image](cmake-build-debug/data/08data.png)
![image](cmake-build-debug/data/012data.png)
![image](cmake-build-debug/data/016data.png)
________________________

## 4. Анализ по сортировкам <br>

### 4.1. Сортировка выбором
![image](cmake-build-debug/data/sorts-graphs/time-50/01sort-time-50.png)
![image](cmake-build-debug/data/sorts-graphs/time-100/01sort-time-100.png)
![image](cmake-build-debug/data/sorts-graphs/count-50/01sort-count-50.png)
![image](cmake-build-debug/data/sorts-graphs/count-100/01sort-count-100.png)

### 4.2. Сортировка пузырьком
![image](cmake-build-debug/data/sorts-graphs/time-50/02sort-time-50.png)
![image](cmake-build-debug/data/sorts-graphs/time-100/02sort-time-100.png)
![image](cmake-build-debug/data/sorts-graphs/count-50/02sort-count-50.png)
![image](cmake-build-debug/data/sorts-graphs/count-100/02sort-count-100.png)

### 4.3. Сортировка пузырьком с условием Айверсона 1
![image](cmake-build-debug/data/sorts-graphs/time-50/03sort-time-50.png)
![image](cmake-build-debug/data/sorts-graphs/time-100/03sort-time-100.png)
![image](cmake-build-debug/data/sorts-graphs/count-50/03sort-count-50.png)
![image](cmake-build-debug/data/sorts-graphs/count-100/03sort-count-100.png)

### 4.4. Сортировка пузырьком с условием Айверсона 1+2
![image](cmake-build-debug/data/sorts-graphs/time-50/04sort-time-50.png)
![image](cmake-build-debug/data/sorts-graphs/time-100/04sort-time-100.png)
![image](cmake-build-debug/data/sorts-graphs/count-50/04sort-count-50.png)
![image](cmake-build-debug/data/sorts-graphs/count-100/04sort-count-100.png)

### 4.5. Сортировка простыми вставками
![image](cmake-build-debug/data/sorts-graphs/time-50/05sort-time-50.png)
![image](cmake-build-debug/data/sorts-graphs/time-100/05sort-time-100.png)
![image](cmake-build-debug/data/sorts-graphs/count-50/05sort-count-50.png)
![image](cmake-build-debug/data/sorts-graphs/count-100/05sort-count-100.png)

### 4.6. Сортировка бинарными вставками
![image](cmake-build-debug/data/sorts-graphs/time-50/06sort-time-50.png)
![image](cmake-build-debug/data/sorts-graphs/time-100/06sort-time-100.png)
![image](cmake-build-debug/data/sorts-graphs/count-50/06sort-count-50.png)
![image](cmake-build-debug/data/sorts-graphs/count-100/06sort-count-100.png)

### 4.7. Сортировка подсчетом (устойчивая)
![image](cmake-build-debug/data/sorts-graphs/time-50/07sort-time-50.png)
![image](cmake-build-debug/data/sorts-graphs/time-100/07sort-time-100.png)
![image](cmake-build-debug/data/sorts-graphs/count-50/07sort-count-50.png)
![image](cmake-build-debug/data/sorts-graphs/count-100/07sort-count-100.png)

### 4.8. Сортировка цифровая (по основанию 256)
![image](cmake-build-debug/data/sorts-graphs/time-50/08sort-time-50.png)
![image](cmake-build-debug/data/sorts-graphs/time-100/08sort-time-100.png)
![image](cmake-build-debug/data/sorts-graphs/count-50/08sort-count-50.png)
![image](cmake-build-debug/data/sorts-graphs/count-100/08sort-count-100.png)

### 4.9. Сортировка слиянием
![image](cmake-build-debug/data/sorts-graphs/time-50/09sort-time-50.png)
![image](cmake-build-debug/data/sorts-graphs/time-100/09sort-time-100.png)
![image](cmake-build-debug/data/sorts-graphs/count-50/09sort-count-50.png)
![image](cmake-build-debug/data/sorts-graphs/count-100/09sort-count-100.png)

### 4.10. Сортировка быстрая (первый эл-т опорный)
![image](cmake-build-debug/data/sorts-graphs/time-50/10sort-time-50.png)
![image](cmake-build-debug/data/sorts-graphs/time-100/10sort-time-100.png)
![image](cmake-build-debug/data/sorts-graphs/count-50/10sort-count-50.png)
![image](cmake-build-debug/data/sorts-graphs/count-100/10sort-count-100.png)

### 4.11. Сортировка пирамидальная
![image](cmake-build-debug/data/sorts-graphs/time-50/11sort-time-50.png)
![image](cmake-build-debug/data/sorts-graphs/time-100/11sort-time-100.png)
![image](cmake-build-debug/data/sorts-graphs/count-50/11sort-count-50.png)
![image](cmake-build-debug/data/sorts-graphs/count-100/11sort-count-100.png)

### 4.12. Сортировка Шелла (последовательность Циура)
![image](cmake-build-debug/data/sorts-graphs/time-50/12sort-time-50.png)
![image](cmake-build-debug/data/sorts-graphs/time-100/12sort-time-100.png)
![image](cmake-build-debug/data/sorts-graphs/count-50/121sort-count-50.png)
![image](cmake-build-debug/data/sorts-graphs/count-100/12sort-count-100.png)

### 4.13. Сортировка Шелла (последовательность Шелла)
![image](cmake-build-debug/data/sorts-graphs/time-50/13sort-time-50.png)
![image](cmake-build-debug/data/sorts-graphs/time-100/13sort-time-100.png)
![image](cmake-build-debug/data/sorts-graphs/count-50/13sort-count-50.png)
![image](cmake-build-debug/data/sorts-graphs/count-100/13sort-count-100.png)

________________________

## 5. Дополнение <br>

Замеры по числу эл-х операций показывают менее хаотичные линии, т.к. это число постоянно при проходе одного и того же массива. На время же могут влиять посторонние процессы + усреднялось всего 10 проходов по времени // дабы долгий вывод не стал дольше... <br>

Данные для графиков можно посмотреть здесь: [data](https://github.com/kseniag03/28-algosi-sorts/tree/origin2/cmake-build-debug/data) <br>
