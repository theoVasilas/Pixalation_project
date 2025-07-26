# Embeded_systems
Pixalation_project

![pixalated](https://user-images.githubusercontent.com/115305797/209630743-23c1bbda-3ded-44a9-bcdd-474b12ce78c1.png)


# 🖼️ YUV Block Averaging with Adaptive Random Block Sizes

The project implicates several improvements for educational purposes and the performances has been measured with ARMulator program

This project implements a YUV image processing tool in C, which reads a `.yuv` file (4:4:4 format), divides it into blocks, and applies **block-based averaging** using randomized adaptive block sizes. The output is a visually simplified version of the input image, with each block having a uniform color equal to the mean of its pixels.

---

## 📌 Features

- ✅ Supports QCIF-format YUV 4:4:4 frames (496×372 resolution)
- ✅ Randomized resizing of horizontal and vertical blocks
- ✅ Adaptive block size correction for dimension mismatch
- ✅ Custom block averaging for Y, U, and V components
- ✅ Efficient I/O using raw buffer operations

---

## 📂 Files

| File | Description |
|------|-------------|
| `main.c` | Main source file containing image processing logic |
| `cherry_496x372_444.yuv` | Sample input YUV file (must exist in working directory) |
| `final_cherry_496x372_444_output.yuv` | Output file with processed image |

---

## 🧠 How It Works

1. **Input**: Raw `.yuv` image in 4:4:4 format (496x372)
2. **Block Division**:
   - Image is divided into `NH x NV` blocks (default: 100 x 100)
   - If the image dimensions are not divisible by the block counts, some blocks are randomly resized by ±1 pixel to cover the full image
3. **Averaging**:
   - Each block’s Y, U, and V values are averaged
   - Every pixel in that block is set to the average value
4. **Output**: The modified YUV frame is saved

---

## 🔧 Parameters

Defined in the source file:

```c
#define N 372  // image height
#define M 496  // image width
#define NH 100 // number of horizontal blocks
#define NV 100 // number of vertical blocks
