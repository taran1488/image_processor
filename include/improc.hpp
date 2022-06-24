#ifndef IMAGE_PROCESSOR_IMPROC_H
#define IMAGE_PROCESSOR_IMPROC_H

#include "bitmap.h"
#include <vector>

#define ARRAY_2D    1
#define VECTOR_OF_VECTORS 2
#define MATRIX_DATA_TYPE VECTOR_OF_VECTORS

<<<<<<< Updated upstream
=======
struct BmpInfoDeleter {
    void operator()(BITMAPINFO* ptr) { delete[] ptr; }
};

using BmpInfoUniquePtr = std::unique_ptr<BITMAPINFO, BmpInfoDeleter>;

BmpInfoUniquePtr copy_bitmapinfo(BITMAPINFO* bmi, BITMAPFILEHEADER hdr);

>>>>>>> Stashed changes
template<class T>
#if MATRIX_DATA_TYPE == ARRAY_2D
using MatrixData = T**;
#else
using MatrixData = std::vector<std::vector<T>>;
#endif

template <typename T>
class Matrix{
public:
    using data_type = MatrixData<T>;
    Matrix(std::size_t r, std::size_t c, T v);
    Matrix(const Matrix& current);
#if MATRIX_DATA_TYPE == ARRAY_2D
    ~Matrix();
<<<<<<< Updated upstream
    std::size_t get_nrows();
    std::size_t get_ncols();
    T& operator[] (std::size_t pos) { return m_[pos]; }
=======
#else
    ~Matrix() = default;
#endif
    std::size_t get_nrows() const;
    std::size_t get_ncols() const;
    void print() const;
#if MATRIX_DATA_TYPE == ARRAY_2D
    T* operator[] (std::size_t pos) { return m_[pos]; }
    const T* operator[] (std::size_t pos) const { return m_[pos]; }
#else
    typename MatrixData<T>::reference operator[] (std::size_t pos) {return m_[pos];}
    typename MatrixData<T>::const_reference operator[] (std::size_t pos) const {return m_[pos];}
#endif
protected:
    data_type m_;
>>>>>>> Stashed changes
private:
    data_type m_;
};
;
class Image{
public:
    BITMAPINFO* bmi = nullptr;
    BITMAPFILEHEADER hdr;
    size_t w;
    size_t h;
    Image(std::size_t h, std::size_t w, BITMAPINFO* bmi, BITMAPFILEHEADER hdr);
    Image(double data): Image(h, w, bmi, hdr) {}
    Image (const Image& i1);
    const BITMAPFILEHEADER& get_bitmapheader();
    BITMAPINFO* get_bitmapinfo();

private:
    double data;
    size_t w;
    size_t h;
};

/**
 * Load a BMP file from the disk.
 *
 * @param filepath File to load.
 * @return The loaded image.
 */
extern byte** load_bitmap(const char* filepath, BITMAPINFO **BitmapInfo);

/**
 * Save a BMP file to disk.
 *
 * @param filepath File to save.
 * @param image Image to save.
 * @return EXIT_SUCCESS on success or EXIT_FAILURE on failure.
 */
extern int save_bitmap(const char* filepath, byte** image, BITMAPINFO* BitmapInfo);

#endif //IMAGE_PROCESSOR_IMPROC_HPP
