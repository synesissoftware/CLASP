/* /////////////////////////////////////////////////////////////////////////
 * File:    clasp/util/search_specifications.hpp
 *
 * Purpose: Utility class for processing search specifications.
 *
 * Created: 20th May 2010
 * Updated: 2nd February 2024
 *
 * Home:    https://github.com/synesissoftware/CLASP/
 *
 * Copyright (c) 2010-2024, Matthew Wilson
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer;
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution;
 * - Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ////////////////////////////////////////////////////////////////////// */


/** \file clasp/util/search_specifications.hpp
 *
 * \brief [C++-only] Utility class for processing search specifications.
 */

#ifndef CLASP_INCL_CLASP_UTIL_HPP_SEARCH_SPECIFICATIONS
#define CLASP_INCL_CLASP_UTIL_HPP_SEARCH_SPECIFICATIONS

/* /////////////////////////////////////////////////////////////////////////
 * version information
 */

#ifndef CLASP_DOCUMENTATION_SKIP_SECTION
# define CLASP_VER_CLASP_UTIL_HPP_SEARCH_SPECIFICATIONS_MAJOR       2
# define CLASP_VER_CLASP_UTIL_HPP_SEARCH_SPECIFICATIONS_MINOR       0
# define CLASP_VER_CLASP_UTIL_HPP_SEARCH_SPECIFICATIONS_REVISION    3
# define CLASP_VER_CLASP_UTIL_HPP_SEARCH_SPECIFICATIONS_EDIT        23
#endif /* !CLASP_DOCUMENTATION_SKIP_SECTION */

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* CLASP header files */
#include <clasp/clasp.hpp>

/* STLSoft header files */
#include <platformstl/filesystem/path.hpp>
#include <platformstl/filesystem/filesystem_traits.hpp>

#include <stlsoft/shims/access/string/fwd.h>
#include <stlsoft/shims/access/string/std/basic_string.hpp>

/* Standard header files */
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

namespace clasp
{

/* /////////////////////////////////////////////////////////////////////////
 * classes
 */

class search_specifications
{
public: // Member Types
  /// The character type
  typedef clasp_char_t                          char_type;
  /// The string type
  typedef clasp_string_t                        string_type;
  /// The boolean type
  typedef bool                                  bool_type;
  /// The size type
  typedef size_t                                size_type;
  /// The specification type
  typedef std::pair<
    string_type
  , string_type
  >                                             specification_type;
private:
  typedef platformstl::filesystem_traits<
    char_type
  >                                             traits_type_;
  typedef std::vector<
    specification_type
  >                                             specifications_type_;
public:
  /// The value type
  typedef specifications_type_::value_type      value_type;
  /// The non-mutating (const) iterator type
  typedef specifications_type_::const_iterator  const_iterator;
  /// The non-mutating (const) reference type
  typedef specifications_type_::const_reference const_reference;

  /// This type
  typedef search_specifications                 class_type;

public: // Member Constants
  enum
  {

  };


public: // Construction
  /**
   *
   * \note When no default directory is specified, all pattern elements
   *  pushed (via push_element()) prior to an explicit pushed directory
   *  will be recorded and then prefixed to any explicit patterns pushed
   *  for each directory.
   */
  search_specifications()
    : m_specifications()
    , m_defaultDirectory()
  {}
  /**
   *
   * \note When a default directory is specified, all pattern elements
   *  pushed (via push_element()) prior to an explicit pushed directory
   *  will be applied to the default directory in the 0th specification.
   */
  search_specifications(string_type const& defaultDirectory)
    : m_specifications()
    , m_defaultDirectory(defaultDirectory)
  {}
private:
  void operator =(class_type const&);
public:
  static search_specifications from_values(
    clasp_arguments_t const* args
  )
  {
    search_specifications specs;

    { for (size_t i = 0; i != args->numValues; ++i)
    {
      clasp_argument_t const& value = args->values[i];

      specs.push_element(string_type(value.value.ptr, value.value.len));
    }}

    return specs;
  }

public: // Operations
  /** Causes enough internal storage to be allocated such that no more
   * storage will be required for \c n elements.
   */
  void reserve(size_type n)
  {
    m_specifications.reserve(n);
  }

  template <typename S>
  bool push_element(S const& element)
  {
    return push_element_(string_type(stlsoft::c_str_data(element), stlsoft::c_str_len(element)));
  }

  /** Pushes an element to create/update a search specification.
   *
   * \param element A directory or a pattern(s).
   *
   * \return Indicates whether the directory or pattern(s) .
   * \retval A corresponding search specification was created/updated.
   * \retval false The element could not be identified as either a directory
   *   or pattern(s), and no corresponding search specification was
   *   created/updated.
   */
  bool push_element(string_type const& element)
  {
    return push_element_(element);
  }

private:
  struct element_is_
  {
    typedef platformstl::filesystem_traits<
      char_type
    >                                 traits_type_;

    enum element_type
    {
      elementIsUnknown,
      elementIsDirectory,
      elementIsPatterns,
    };

    static
    element_type
    directory(
      char_type const* path
    )
    {
      traits_type_::stat_data_type sd;

      if (!traits_type_::stat(path, &sd))
      {
        return elementIsUnknown;
      }
      else
      {
        if (traits_type_::is_directory(&sd))
        {
          return elementIsDirectory;
        }
        else
        {
          return elementIsPatterns;
        }
      }
    }
  };

  bool push_element_(string_type const& element)
  {
    STLSOFT_ASSERT(!element.empty());

    element_is_::element_type type = element_is_::elementIsUnknown;

    static clasp_char_t const   dot1[]  =   { '.', '\0' };
    static clasp_char_t const   dot2[]  =   { '.', '.', '\0' };

    // Is dots directory?
    if (dot1 == element ||
        dot2 == element)
    {
      type = element_is_::elementIsDirectory;
    }
    // Contains path separator?
    else if (element.end() != std::find_if(element.begin(), element.end(), is_path_separator))
    {
      type = element_is_::elementIsPatterns;
    }
    // Contains wildcard character?
    else if (element.end() != std::find_if(element.begin(), element.end(), is_wildcard_character))
    {
      type = element_is_::elementIsPatterns;
    }
    // Has trailing path-name separator
    else if (traits_type_::is_path_name_separator(element[element.size() - 1u]))
    {
      type = element_is_::elementIsDirectory;
    }
    //
    else if (traits_type_::is_path_absolute(element.c_str()) ||
            traits_type_::is_path_rooted(element.c_str()))
    {
      type = element_is_::directory(element.c_str());
    }

    if (element_is_::elementIsUnknown == type)
    {
      // Remaining determinations based on existence (or lack of) of entries

      typedef platformstl::basic_path<char_type> path_t;

      if (!m_specifications.empty())
      {
        specification_type const& current = m_specifications.back();

        path_t  fullPath1(current.first);

        fullPath1.make_absolute();

        fullPath1 /= element;

        type = element_is_::directory(fullPath1.c_str());
      }

      if (element_is_::elementIsUnknown == type)
      {
        // No current directory, so go from current directory
        path_t fullPath0(".");

        fullPath0.make_absolute();

        fullPath0 /= element;

        type = element_is_::directory(fullPath0.c_str());
      }
    }

    if (element_is_::elementIsUnknown == type)
    {
      return false;
    }
    else if (element_is_::elementIsDirectory == type)
    {
      // A new directory

      push_directory(element);

      return true;
    }
    else
    {
      STLSOFT_ASSERT(element_is_::elementIsPatterns == type);

      push_patterns(element);

      return true;
    }
  }
public:

  /** Pushes a directory element to create/update a search specification.
   *
   * \param element The directory.
   */
  void push_directory(string_type const& element)
  {
    m_specifications.push_back(std::make_pair(element, m_commonPatterns));
  }

  /** Pushes a patterns element to create/update a search specification.
   *
   * \param element The patterns.
   */
  void push_patterns(string_type const& element)
  {
    bool const isEmpty = m_specifications.empty();

    // A pattern

    if (isEmpty &&
        m_defaultDirectory.empty())
    {
      m_commonPatterns.reserve(m_commonPatterns.length() + 1 + element.length());
      if (!m_commonPatterns.empty())
      {
        m_commonPatterns += '|';
      }
      m_commonPatterns += element;
    }
    else
    {
      try
      {
        if (isEmpty)
        {
          // A new directory
          m_specifications.push_back(std::make_pair(m_defaultDirectory, m_commonPatterns));
        }

        string_type& patterns = m_specifications.back().second;

        if (element != patterns)
        {
          patterns.reserve(patterns.length() + 1 + element.length());
          if (!m_specifications.back().second.empty())
          {
            m_specifications.back().second += '|';
          }
          m_specifications.back().second += element;
        }
      }
      catch(...)
      {
        if (isEmpty)
        {
          m_specifications.erase(m_specifications.begin(), m_specifications.end());
        }

        throw;
      }
    }
  }

  /** Applies the given pattern(s) to any specifications that have empty
   * patterns
   *
   * \param defaultPatterns The default pattern(s)
   */
  void apply_default_patterns(string_type const& defaultPatterns)
  {
    { for (specifications_type_::iterator i = m_specifications.begin(); i != m_specifications.end(); ++i)
    {
      string_type& patterns = (*i).second;

      if (patterns.empty())
      {
        patterns = defaultPatterns;
      }
    }}
  }

public: // Attributes

  /** Indicates whether the instance contains any search specifications.
   */
  bool_type   empty() const
  {
    return 0u == size();
  }

  /** The number of search specifications
   *
   * \note If a default directory is specified, this will always
   *   be at least 1
   */
  size_type size() const
  {
    return m_specifications.size();
  }

  /** Obtains a non-mutating (const) reference to the search specification
   * at the given index.
   *
   * \param index The
   *
   * \pre index < size()
   */
  const_reference operator [](size_type index) const
  {
    STLSOFT_ASSERT(index < size());

    return m_specifications[index];
  }

public: // Iteration
  const_iterator begin() const
  {
    return m_specifications.begin();
  }
  const_iterator end() const
  {
    return m_specifications.end();
  }

private: // Implementation
  static traits_type_::bool_type is_path_separator(char_type ch)
  {
    return '|' == ch || traits_type_::path_separator() == ch;
  }
  static traits_type_::bool_type is_wildcard_character(char_type ch)
  {
    return '?' == ch || '*' == ch;
  }

private: // Fields
  specifications_type_  m_specifications;
  string_type const     m_defaultDirectory;
  string_type           m_commonPatterns;
};

/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

} /* namespace clasp */

/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !CLASP_INCL_CLASP_UTIL_HPP_SEARCH_SPECIFICATIONS */

/* ///////////////////////////// end of file //////////////////////////// */

