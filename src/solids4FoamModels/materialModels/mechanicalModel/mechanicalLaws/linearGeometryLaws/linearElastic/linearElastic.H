/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | foam-extend: Open Source CFD
   \\    /   O peration     |
    \\  /    A nd           | For copyright notice see file Copyright
     \\/     M anipulation  |
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
    linearElastic

Description
    Hookean linear elastic mechanical law.

SourceFiles
    linearElastic.C

Author
    Philip Cardiff, UCD. All rights reserved

\*---------------------------------------------------------------------------*/

#ifndef linearElastic_H
#define linearElastic_H

#include "mechanicalLaw.H"
#include "surfaceMesh.H"
#include "zeroGradientFvPatchFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                         Class linearElastic Declaration
\*---------------------------------------------------------------------------*/

class linearElastic
:
    public mechanicalLaw
{
    // Private data

        //- Shear modulus (second Lame parameter)
        dimensionedScalar mu_;

        //- Bulk modulus
        dimensionedScalar K_;

        //- Young's modulus
        dimensionedScalar E_;

        //- Poisson's ratio
        dimensionedScalar nu_;

        //- First Lame parameter
        dimensionedScalar lambda_;

        //- Initial (residual) stress surface field
        mutable autoPtr<surfaceSymmTensorField> sigma0fPtr_;

    // Private Member Functions

        //- Make the initial stress surface field
        void makeSigma0f() const;

        //- Return a const reference to the initial stress surface field
        const surfaceSymmTensorField& sigma0f() const;

        //- Return a non-const reference to the initial stress surface field
        surfaceSymmTensorField& sigma0f();

        //- Disallow default bitwise copy construct
        linearElastic(const linearElastic&);

        //- Disallow default bitwise assignment
        void operator=(const linearElastic&);

public:

    //- Runtime type information
    TypeName("linearElastic");

    // Static data members


    // Constructors

        //- Construct from dictionary
        linearElastic
        (
            const word& name,
            const fvMesh& mesh,
            const dictionary& dict,
            const nonLinearGeometry::nonLinearType& nonLinGeom
        );


    // Destructor

        virtual ~linearElastic()
        {}


    // Member Functions

        //- Return bulk modulus
        virtual tmp<volScalarField> bulkModulus() const;

        //- Return the implicit stiffness
        //  This is the diffusivity for the Laplacian term
        virtual tmp<volScalarField> impK() const;

        //- Material tangent for Newton Raphson loop
        virtual symmTensor4thOrder materialTangent() const;

        //- Provide access to mu for the coupledUnsNonLinLinearElasticSolid
        virtual const dimensionedScalar& mu() const;

        //- Bulk modulus
        virtual const dimensionedScalar& K() const;

        //- Young's modulus
        virtual const dimensionedScalar& E() const;

        //- Poisson's ratio
        virtual const dimensionedScalar& nu() const;

        //- Lambda
        virtual const dimensionedScalar& lambda() const;

        //- Calculate the stress
        virtual void correct(volSymmTensorField& sigma);

        //- Calculate the stress
        virtual void correct(surfaceSymmTensorField& sigma);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
