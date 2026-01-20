---
title: C++ - Allocation mémoire et structure RAII
version: 1.0.0
theme: default
footer: Thomas Le Goff - 2025 - CC BY-NC-SA
header: C++ - Allocation mémoire et structure RAII - BTS CIEL
paginate: true
marp: true
style: |-
  section {
    font-size: 1.6em;
  }

  img[alt~="center"] {
    display: block;
    margin: 0 auto;
  }

  section.lead h1 {
    text-align: center;
  }

  section.gridify {
    display: grid;
    grid-template:
      "title title title" auto
      "left left   right" 1fr
      / 1fr 1fr;
    gap: 0 1rem;
    align-items: start;
  }

  section.gridify > h2 {
    grid-area: title;
  }

  section.gridify > pre:nth-of-type(1) {
    grid-area: left;
  }

  section.gridify > pre:nth-of-type(2) {
    grid-area: right;
  }
---

# C++ - Allocation mémoire et structure RAII

_BTS CIEL_

![bg right:40%](./img/c++_raii_cover.jpg)

--------------------------------------------------------------------------------

<!-- _class: gridify -->

## Rappel stack VS heap en C

```c
void add(int a, int b)
{
  return a + b;
}

int main()
{
  int a = 10;
  int b = 12;

  int result = add(a, b);

  printf("Result: %d", result);

  return 0;
}
```
![height:550px](img/c_stack.drawio.svg)

--------------------------------------------------------------------------------

<!-- _class: gridify -->

## Rappel stack VS heap en C

```c
typedef struct Point {int x; int y;} Point;

Point* new_point_from(Point a, Point b)
{
  Point* p = malloc(sizeof(Point));

  if (p == NULL) return NULL;

  p->x = a.x + b.x;
  p->y = a.y + b.y;

  return p;
}

int main()
{
  Point a = {10, 10};
  Point b = {20, 20};
  Point* p = new_point_from(a, b);
  free(p);
}
```

![height:550px](img/c_stack_heap.drawio.svg)

--------------------------------------------------------------------------------

<!-- _class: gridify -->

## C++ new et delete

```c++
struct Point {int x; int y;};

Point* new_point_from(Point a, Point b)
{
  Point* p = new Point();

  p->x = a.x + b.x;
  p->y = a.y + b.y;

  return p;
}

int main()
{
  Point a = {10, 10};
  Point b = {20, 20};
  Point* p = new_point_from(a, b);
  delete p;
}
```

![height:550px](img/cpp_new_delete.drawio.svg)

--------------------------------------------------------------------------------

<!-- _class: gridify -->

## C++ référence

```c++
struct Point {int x; int y;};

Point* new_point_from(Point& a, Point& b)
{
  Point* p = new Point();

  p->x = a.x + b.x;
  p->y = a.y + b.y;

  return p;
}

int main()
{
  Point a = {10, 10};
  Point b = {20, 20};
  Point* p = new_point_from(a, b);
  delete p;
}
```

![height:550px](img/cpp_new_delete.drawio.svg)

--------------------------------------------------------------------------------

<!-- _class: gridify -->

## C++ constructeur et destructeur

```c++
struct Point {
  int x; int y;

  Point(int _x, int _y) : x(_x), y(_y) {}
  ~Point() {}
};

Point* new_point_from(Point& a, Point& b)
{
  Point* p = new Point(0, 0);

  p->x = a.x + b.x;
  p->y = a.y + b.y;

  return p;
}

int main()
{
  Point a = {10, 10};
  Point b = {20, 20};
  Point* p = new_point_from(a, b);
  delete p;
}
```

![height:550px](img/cpp_constructor_destructor.drawio.svg)

--------------------------------------------------------------------------------

<!-- _class: gridify -->

## C++ RAII

```c++
struct Point {int x; int y;};

int main()
{
  std::vector<Point> points = {};

  points.push_back(Point(10, 5));
  points.push_back(Point(20, 13));
}
```

![height:550px](img/cpp_vector.drawio.svg)