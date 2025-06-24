# 📊 Cuddle - DataFrame Library in C

Cuddle is a C library that allows you to easily manipulate CSV files as DataFrames, similar to pandas in Python. It provides functions to read, write, filter, sort, group, transform, and describe tabular data.

## 🚀 Installation

### Compilation

To compile the library, go to the root of the project and run:

```sh
make
```

This generates the static library `libcuddle.a` in the current directory.

### Cleaning

To clean object files:

```sh
make clean
```

To remove the compiled library:

```sh
make fclean
```

## 📚 Usage

Include the header in your project:

```c
#include "dataframe.h"
```

Link the library when compiling:

```sh
gcc your_program.c -L. -lcuddle -o your_program
```

## ✨ Main Functions

### Reading and Writing

- **Read a CSV**  
  ```c
  dataframe_t *df = df_read_csv("file.csv", ";");
  ```
- **Write a CSV**  
  ```c
  df_write_csv(df, "new.csv");
  ```

### Exploration

- **Show column info**  
  ```c
  df_info(df);
  ```
- **Show first rows**  
  ```c
  dataframe_t *head = df_head(df, 5);
  ```
- **Show last rows**  
  ```c
  dataframe_t *tail = df_tail(df, 5);
  ```
- **Describe numeric columns**  
  ```c
  df_describe(df);
  ```

### Manipulation

- **Filter**  
  ```c
  dataframe_t *filtered = df_filter(df, "column", predicate_func);
  ```
- **Sort**  
  ```c
  dataframe_t *sorted = df_sort(df, "column", compare_func);
  ```
- **GroupBy (doesn't work)**  
  ```c
  dataframe_t *grouped = df_groupby(df, "column", columns_to_aggregate, agg_func);
  ```
- **Apply a function**  
  ```c
  dataframe_t *applied = df_apply(df, "column", apply_func);
  ```

### Data Access

- **Get a value**  
  ```c
  void *val = df_get_value(df, 0, "column");
  ```
- **Get all values from a column**  
  ```c
  void **vals = df_get_values(df, "column");
  ```

### Memory Management

Don't forget to free the memory at the end:

```c
df_free(df);
```

## 📝 Minimal Example

```c
#include "dataframe.h"

int main(void)
{
    dataframe_t *df = df_read_csv("data.csv", ";");

    if (!df)
      return 1;
    df_info(df);
    df_describe(df);
    df_free(df);
    return 0;
}
```

## 📄 Project Structure

- `include/`: public headers
- `src/`: library source code
- `libcuddle.a`: compiled library
- `main.c`: usage example

## 🛠️ Dependencies

No external dependencies, only the standard C library.

## 👨‍💻 Author

```c
void Alexandro_Almeida()
{
    printf("First-year project\n");
    printf("Created by me and Mathis Loiseau\n");
    printf("Thank you for reading the README :)\n");
}
```