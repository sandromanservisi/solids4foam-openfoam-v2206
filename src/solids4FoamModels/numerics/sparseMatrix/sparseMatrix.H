/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | foam-extend: Open Source CFD
   \\    /   O peration     | Version:     3.2
    \\  /    A nd           | Web:         http://www.foam-extend.org
     \\/     M anipulation  | For copyright notice see file Copyright
-------------------------------------------------------------------------------
License
    This file is part of foam-extend.

    foam-extend is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    foam-extend is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with foam-extend.  If not, see <http://www.gnu.org/licenses/>.

Class
    sparseMatrix

Description
    A simple but convenient matrix for storing sparse matrices.
    Values are stored using a HashTable where the Hash is based on the
    (rowI, columns) key.

    For now, it is assumed that every value is a tensor, but the intention is to
    template this.

    Used in coupled solid mechanics solvers in solids4foam.

    Example usage:

        sparseMatrix mat;
        mat(1, 0) = tensor(1,2,3,4,5,6,7,8,9);
        mat(0, 2) += 3*I;

Author
    Philip Cardiff, UCD.

SourceFiles
    sparseMatrix.C

\*---------------------------------------------------------------------------*/

#ifndef sparseMatrix_H
#define sparseMatrix_H

#include "HashTable.H"
#include "FixedList.H"
#include "tensor.H"
#include "refCount.H"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

    typedef HashTable
    <
        tensor, FixedList<label, 2>, FixedList<label, 2>::Hash<>
    > sparseMatrixData;

/*---------------------------------------------------------------------------*\
                       Class sparseMatrix Declaration
\*---------------------------------------------------------------------------*/

class sparseMatrix
:
    public refCount
{
    // Private data

        //- Hashtable (map) where the values are stored
        sparseMatrixData data_;


    // Private Member Functions

        //- Disallow default bitwise copy construct
        sparseMatrix(const sparseMatrix&);

        //- Disallow default bitwise assignment
        void operator=(const sparseMatrix&);

public:

    //- Runtime type information
    TypeName("sparseMatrix");


    // Constructors

        //- Construct given approximate size
        sparseMatrix(const label size = 128);


    // Destructor

        virtual ~sparseMatrix()
        {}


    // Member Functions

        // Access

            //- Const access to the data
            const sparseMatrixData& data() const
            {
                return data_;
            }

            //- Non-const access to the data
            sparseMatrixData& data()
            {
                return data_;
            }

            //- Count and return the number of block rows in the matrix
            label nBlockRows() const;

        // Modifiers

            //- Clear the matrix but do not change its capacity
            void clear()
            {
                data_.clear();
            }

        // Operators

            //- Non-const access to a value entry. If the entry does not exist
            //  then create it and initialise it to zero
            tensor& operator()(const label rowI, const label colI);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
