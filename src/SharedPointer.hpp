/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SharedPointer.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:56:06 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/27 12:37:21 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>

template <class T>
class SharedPointer
{
    public:

        SharedPointer()
        {
            m_object = NULL;
            m_ref_count = NULL;
        }

        SharedPointer(T const& object)
        {
            m_object = new T(object);
            m_ref_count = new unsigned int(1);
        }

        SharedPointer(SharedPointer const& ref)
        {
            m_object = ref.m_object;
            m_ref_count = ref.m_ref_count;
            if (m_ref_count)
                (*m_ref_count)++;
        }

        SharedPointer& operator=(SharedPointer const& ref)
        {
            if (m_object != ref.m_object)
            {
                if (m_ref_count)
                {
                    clear();
                }
                m_object = ref.m_object;
                m_ref_count = ref.m_ref_count;
                (*m_ref_count)++;
            }
            return (*this);
        }

        T& operator*()
        {
            return *m_object;
        }

        T const& operator*() const
        {
            return *m_object;
        }

        T* operator->()
        {
            return m_object;
        }

        T const* operator->() const
        {
            return m_object;
        }

        ~SharedPointer()
        {
            if (m_ref_count)
                clear();
        }

        T* get()
        {
            return m_object;
        }

        T const* get() const
        {
            return m_object;
        }

        void    clear()
        {
            (*m_ref_count)--;
            if (!*m_ref_count)
            {
                delete m_object;
                delete m_ref_count;
                m_object = NULL;
                m_ref_count = NULL;
            }
        }

    private:
        T* m_object;
        unsigned int* m_ref_count;

};