#ifndef CUIMG_HOST_IMAGE2D_HPP_
# define CUIMG_HOST_IMAGE2D_HPP_

# include <cuimg/cpu/host_image2d.h>
# include <cuimg/error.h>
# include <cuimg/free.h>

namespace cuimg
{


  template <typename V>
  host_image2d<V>::host_image2d()
  {
  }

  template <typename V>
  host_image2d<V>::host_image2d(unsigned nrows, unsigned ncols, bool pinned)
    : domain_(nrows, ncols),
      pitch_(ncols * sizeof(V))
  {
    allocate(domain_, pinned);
  }

  template <typename V>
  host_image2d<V>::host_image2d(const domain_type& d, bool pinned)
    : domain_(d),
      pitch_(ncols() * sizeof(V))
  {
    allocate(domain_, pinned);
  }

  template <typename V>
  void
  host_image2d<V>::allocate(const domain_type& d, bool pinned)
  {
    V* ptr;

#ifndef NO_CUDA
    if (pinned)
    {
      cudaMallocHost(&ptr, domain_.nrows() * domain_.ncols() * sizeof(V));
      data_ = boost::shared_ptr<V>(ptr, cudaFreeHost);
    }
    else
#endif
    {
      ptr = new V[domain_.nrows() * domain_.ncols()];
      data_ = boost::shared_ptr<V>(ptr, array_free<V>);
    }

    buffer_ = data_.get();
  }


  template <typename V>
  host_image2d<V>::host_image2d(const host_image2d<V>& img)
    : domain_(img.domain()),
      pitch_(img.pitch()),
      data_(img.data_)
  {
    buffer_ = data_.get();
  }

  template <typename V>
  host_image2d<V>&
  host_image2d<V>::operator=(const host_image2d<V>& img)
  {
    domain_ = img.domain();
    pitch_ = img.pitch();
    data_ = img.data_;
    buffer_ = data_.get();
    return *this;
  }

  template <typename V>
  const typename host_image2d<V>::domain_type& host_image2d<V>::domain() const
  {
    return domain_;
  }

  template <typename V>
  unsigned host_image2d<V>::nrows() const
  {
    return domain_.nrows();
  }
  template <typename V>
  unsigned host_image2d<V>::ncols() const
  {
    return domain_.ncols();
  }

  template <typename V>
  bool host_image2d<V>::has(const point& p) const
  {
    return domain_.has(p);
  }

  template <typename V>
  inline size_t host_image2d<V>::pitch() const
  {
    return pitch_;
  }

  template <typename V>
  inline V* host_image2d<V>::data()
  {
    return data_.get();
  }

  template <typename V>
  inline const V* host_image2d<V>::data() const
  {
    return data_.get();
  }

  template <typename V>
  inline size_t host_image2d<V>::buffer_size() const
  {
    return sizeof(V) * nrows() * ncols();
  }

  template <typename V>
  inline V& host_image2d<V>::operator()(const point& p)
  {
    return buffer_[p.row() * domain_.ncols() + p.col()];
  }

  template <typename V>
  inline const V& host_image2d<V>::operator()(const point& p) const
  {
    return buffer_[p.row() * domain_.ncols() + p.col()];
  }

  template <typename V>
  inline V&
  host_image2d<V>::operator()(int r, int c)
  {
    return operator()(point(r, c));
  }

  template <typename V>
  inline const V&
  host_image2d<V>::operator()(int r, int c) const
  {
    return operator()(point(r, c));
  }

}

#endif
