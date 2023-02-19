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

С массивами небольшого размера, состоящими из практически одинаковых элементов, хуже всего работают быстрая сортировка (по времени) и сортировка пузырьком, независимо от доп. условий (по эл-м операциям), т.к. все элементы в заданном входном массиве одинаковы (опорный эл-т быстрой не может разделить входной массив на два => сложность значительно возрастает). <br>
Лучше всего с ними работает сортировка подсчётом, т.к. всего элементов мало + на числовой прямой они расположены очень близко друг к другу.

### 3.2. 0-4000
![image](cmake-build-debug/data/02data.png)
![image](cmake-build-debug/data/06data.png)
![image](cmake-build-debug/data/010data.png)
![image](cmake-build-debug/data/014data.png)

С массивами небольшого размера, состоящими из элементов широкого диапазона, хуже всего работают быстрая сортировка (по времени) и сортировка пузырьком, независимо от доп. условий (по эл-м операциям) <br>
Лучше всего с ними работают Шелл, пирамидальная и цифровая.

### 3.3. почти-отсортированный
![image](cmake-build-debug/data/03data.png)
![image](cmake-build-debug/data/07data.png)
![image](cmake-build-debug/data/011data.png)
![image](cmake-build-debug/data/015data.png)

С почти отсортированными массивами небольшого размера, состоящими из элементов широкого диапазона, хуже всего работают быстрая сортировка (по времени и эл-м операциям) <br>
Лучше всего с ними работают вставки (простые и бинарные), т.к. меньше эл-в надо будет сдвигать. <br>

### 3.4. отсортированный-по-убыванию
![image](cmake-build-debug/data/04data.png)
![image](cmake-build-debug/data/08data.png)
![image](cmake-build-debug/data/012data.png)
![image](cmake-build-debug/data/016data.png)

С массивами небольшого размера, состоящими из элементов широкого диапазона, хуже всего работают быстрая сортировка (по времени) и сортировка пузырьком, независимо от доп. условий (по эл-м операциям), т.к. у быстрой сортировки выбираем первый эл-т и при разделении получаем два несбалансированных массива. <br>
Лучше всего с ними работают Шелл, пирамидальная и цифровая, также подсчётом (если диапазон данных не слишком широкий). <br>
________________________

## 4. Анализ по сортировкам

### 4.1. Сортировка выбором
![image](cmake-build-debug/data/sorts-graphs/time-50/01sort-time-50.png)
![image](cmake-build-debug/data/sorts-graphs/time-100/01sort-time-100.png)
![image](cmake-build-debug/data/sorts-graphs/count-50/01sort-count-50.png)
![image](cmake-build-debug/data/sorts-graphs/count-100/01sort-count-100.png)

Хуже всего работает на отсортированных в обратном порядке -- при больших размерах; на почти отсортированных -- при меньших размерах <br>
Лучше всего работает -- наоборот <br>

### 4.2. Сортировка пузырьком
![image](cmake-build-debug/data/sorts-graphs/time-50/02sort-time-50.png)
![image](cmake-build-debug/data/sorts-graphs/time-100/02sort-time-100.png)
![image](cmake-build-debug/data/sorts-graphs/count-50/02sort-count-50.png)
![image](cmake-build-debug/data/sorts-graphs/count-100/02sort-count-100.png)

Хуже всего работает на отсортированных в обратном порядке <br>
Лучше всего работает на почти отсортированных <br>

### 4.3. Сортировка пузырьком с условием Айверсона 1
![image](cmake-build-debug/data/sorts-graphs/time-50/03sort-time-50.png)
![image](cmake-build-debug/data/sorts-graphs/time-100/03sort-time-100.png)
![image](cmake-build-debug/data/sorts-graphs/count-50/03sort-count-50.png)
![image](cmake-build-debug/data/sorts-graphs/count-100/03sort-count-100.png)

Менее хаотична по сравнению с пузырьком без условия <br>
Хуже всего работает на отсортированных в обратном порядке <br>
Лучше всего работает на почти отсортированных, причём лучше безусловной, т.к. там меньше операций из-за условий <br>

### 4.4. Сортировка пузырьком с условием Айверсона 1+2
![image](cmake-build-debug/data/sorts-graphs/time-50/04sort-time-50.png)
![image](cmake-build-debug/data/sorts-graphs/time-100/04sort-time-100.png)
![image](cmake-build-debug/data/sorts-graphs/count-50/04sort-count-50.png)
![image](cmake-build-debug/data/sorts-graphs/count-100/04sort-count-100.png)

Показывает результаты похуже условия 1 и безусловного на близко расположенных на прямой данных (массив небольшого размера) <br>
Хуже всего работает на отсортированных в обратном порядке <br>
Лучше всего работает на почти отсортированных, причём лучше безусловной, т.к. там меньше операций из-за условий  <br>

### 4.5. Сортировка простыми вставками
![image](cmake-build-debug/data/sorts-graphs/time-50/05sort-time-50.png)
![image](cmake-build-debug/data/sorts-graphs/time-100/05sort-time-100.png)
![image](cmake-build-debug/data/sorts-graphs/count-50/05sort-count-50.png)
![image](cmake-build-debug/data/sorts-graphs/count-100/05sort-count-100.png)

Хуже всего работает на отсортированных в обратном порядке <br>
Лучше всего работает на почти отсортированных <br>

### 4.6. Сортировка бинарными вставками
![image](cmake-build-debug/data/sorts-graphs/time-50/06sort-time-50.png)
![image](cmake-build-debug/data/sorts-graphs/time-100/06sort-time-100.png)
![image](cmake-build-debug/data/sorts-graphs/count-50/06sort-count-50.png)
![image](cmake-build-debug/data/sorts-graphs/count-100/06sort-count-100.png)

Показывает результаты похуже простых вставок на близко расположенных на прямой данных (массив небольшого размера) из-за "сломанного" бинпоиска <br>
Хуже всего работает на отсортированных в обратном порядке <br>
Лучше всего работает на почти отсортированных <br>

### 4.7. Сортировка подсчетом (устойчивая)
![image](cmake-build-debug/data/sorts-graphs/time-50/07sort-time-50.png)
![image](cmake-build-debug/data/sorts-graphs/time-100/07sort-time-100.png)
![image](cmake-build-debug/data/sorts-graphs/count-50/07sort-count-50.png)
![image](cmake-build-debug/data/sorts-graphs/count-100/07sort-count-100.png)

Хорошо работает на близко расположенных на прямой данных, на остальных -- практически одинаково плохо <br>

### 4.8. Сортировка цифровая (по основанию 256)
![image](cmake-build-debug/data/sorts-graphs/time-50/08sort-time-50.png)
![image](cmake-build-debug/data/sorts-graphs/time-100/08sort-time-100.png)
![image](cmake-build-debug/data/sorts-graphs/count-50/08sort-count-50.png)
![image](cmake-build-debug/data/sorts-graphs/count-100/08sort-count-100.png)

Суетливая какая-то... <br>
По элементарным операциям стабильно одинаково <br>
На небольших массивах выделяется преимущество данных широкого диапазона <br>

### 4.9. Сортировка слиянием
![image](cmake-build-debug/data/sorts-graphs/time-50/09sort-time-50.png)
![image](cmake-build-debug/data/sorts-graphs/time-100/09sort-time-100.png)
![image](cmake-build-debug/data/sorts-graphs/count-50/09sort-count-50.png)
![image](cmake-build-debug/data/sorts-graphs/count-100/09sort-count-100.png)

Хорошо работает с данными широкого диапазона, плохо -- с близко расположенными <br>
На больших массивах стабильно хаотична <br>
Меньше всего эл-х операций при работе с обратно отсортированными данными, больше -- с данными широкого диапазона <br>

### 4.10. Сортировка быстрая (первый эл-т опорный)
![image](cmake-build-debug/data/sorts-graphs/time-50/10sort-time-50.png)
![image](cmake-build-debug/data/sorts-graphs/time-100/10sort-time-100.png)
![image](cmake-build-debug/data/sorts-graphs/count-50/10sort-count-50.png)
![image](cmake-build-debug/data/sorts-graphs/count-100/10sort-count-100.png)

Лучше работает с данными широкого диапазона, плохо -- с почти отсортированными, с ростом размера массива (по времени и числу операций) <br>
Аномальный провал при размере около 3750... <br>

### 4.11. Сортировка пирамидальная
![image](cmake-build-debug/data/sorts-graphs/time-50/11sort-time-50.png)
![image](cmake-build-debug/data/sorts-graphs/time-100/11sort-time-100.png)
![image](cmake-build-debug/data/sorts-graphs/count-50/11sort-count-50.png)
![image](cmake-build-debug/data/sorts-graphs/count-100/11sort-count-100.png)

При меньших размерах лучше на обратно отсортированных данных, при больших -- на близко расположенных <br>
На почти отсортированных и данных широкого диапазона работает хуже <br>
По эл-м операциям чёткая градация: почти отсортированные > данные широкого диапазона > обратно отсортированные > близко расположенные <br>

### 4.12. Сортировка Шелла (последовательность Циура)
![image](cmake-build-debug/data/sorts-graphs/time-50/12sort-time-50.png)
![image](cmake-build-debug/data/sorts-graphs/time-100/12sort-time-100.png)
![image](cmake-build-debug/data/sorts-graphs/count-50/12sort-count-50.png)
![image](cmake-build-debug/data/sorts-graphs/count-100/12sort-count-100.png)

Плохо работает на близко расположенных при меньших размерах, на далеко расположенных -- при больших <br>
Хорошо на почти отсортированных (везде) и на близко расположенных при больших размерах (лучше при счёте операций) <br>

### 4.13. Сортировка Шелла (последовательность Шелла)
![image](cmake-build-debug/data/sorts-graphs/time-50/13sort-time-50.png)
![image](cmake-build-debug/data/sorts-graphs/time-100/13sort-time-100.png)
![image](cmake-build-debug/data/sorts-graphs/count-50/13sort-count-50.png)
![image](cmake-build-debug/data/sorts-graphs/count-100/13sort-count-100.png)

Схожа с послед-ю Циура по тенденциям графиков, но диапазон значений выше (т.е. работает медленнее) <br>
Хорошо на почти отсортированных (везде) и на близко расположенных при больших размерах <br>
Сильный скачок вверх по данным широкого диапазона с ростом размера массива <br>
________________________

## 5. Дополнение <br>

Данные для графиков можно посмотреть здесь: [data](https://github.com/kseniag03/28-algosi-sorts/tree/origin2/cmake-build-debug/data) <br>

Замеры по числу эл-х операций показывают менее хаотичные линии, т.к. это число постоянно при проходе одного и того же массива. На время же могут влиять посторонние процессы + усреднялось всего 10 проходов по времени // дабы долгий вывод не стал дольше... <br>

Итак, массивы небольшого размера лучше сортировать Шеллом, слияние, цифровой, вставками (лучше, если почти отсортированы),  можно также подсчётом (если эл-ы не сильно различаются). <br>

Массивы с близко расположенными данными лучше сортировать подсчётом, цифровой, слиянием или Шеллом. Пузырёк не использовать на массивах любого размера, и быструю (по замерах времени плоха). <br>

Массивы с больших разбросом данных лучше сортировать цифровой, слиянием или Шеллом. Чем больше будет раздброс между элементами, тем хуже будет работать подсчёт. <br>

На почти и обратно отсортированных массивах лучше использовать Шелла, слияние, цифровую и сортировку вставками (лучше на массивах меньшего размера), можно также подсчётом (если эл-ы не сильно различаются). <br>

Сортировка кучей имеет гарантированную сложность nlogn, поэтому везде показывает средние результаты. <br>
