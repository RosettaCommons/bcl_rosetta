// (c) Copyright BCL @ Vanderbilt University 2014
// (c) BCL Homepage: http://www.meilerlab.org/bclcommons
// (c) BCL Code Repository: https://github.com/BCLCommons/bcl
// (c)
// (c) The BioChemical Library (BCL) was originally developed by contributing members of the Meiler Lab @ Vanderbilt University.
// (c)
// (c) The BCL is now made available as an open-source software package distributed under the permissive MIT license,
// (c) developed and maintained by the Meiler Lab at Vanderbilt University and contributing members of the BCL Commons.
// (c)
// (c) External code contributions to the BCL are welcome. Please visit the BCL Commons GitHub page for information on how you can contribute.
// (c)
// (c) This file is part of the BCL software suite and is made available under the MIT license.
// (c)

#ifndef BCL_SCORESTAT_OLS_H_
#define BCL_SCORESTAT_OLS_H_

// include the namespace header
#include "bcl_scorestat.h"

// include other forward headers - sorted alphabetically
#include "biol/bcl_biol.fwd.hh"

// includes from bcl - sorted alphabetically
#include "assemble/bcl_assemble_analyze_protein_ensemble_interface.h"
#include "assemble/bcl_assemble_protein_model.h"
#include "math/bcl_math_histogram.h"
#include "storage/bcl_storage_table.h"
#include "storage/bcl_storage_vector.h"

// external includes - sorted alphabetically

namespace bcl
{
  namespace scorestat
  {
    /////////////////////////////////////////////////////////////////////
    //!
    //! @class OLS
    //! @brief extracts sasa overlapping sphere statistics from protein models
    //!
    //! @see @link example_scorestat_ols.cpp @endlink
    //! @author lib14
    //! @date May 18th, 2015
    //////////////////////////////////////////////////////////////////////

    class BCL_API OLS :
      public assemble::AnalyzeProteinEnsembleInterface
    {

    public:

      //! chain options, compute neighbor count considering only one chain or all chains
      enum ChainOption
      {
        e_OneChain,
        e_AllChains,
        s_NumberChainOptions
      };

      //! @brief ChainOption as string
      //! @param CHAIN_OPTION the ChainOption
      //! @return the string for the ChainOption
      static const std::string &GetChainOptionName( const ChainOption &CHAIN_OPTION);

      //! @brief Output filename as string
      //! @param ChainOption the desired Output Type
      //! @return the string for the output file extension
      static const std::string &GetOutputFileName( const ChainOption &CHAIN_OPTION, const bool SPLIT_ENVIRONMENT);

      //! @brief OutputOptionEnum enum I/O helper
      typedef util::WrapperEnum< ChainOption, &GetChainOptionName, s_NumberChainOptions> ChainOptionEnum;

    private:

    //////////
    // data //
    //////////

      //! output options
      ChainOptionEnum m_ChainOption;

      //! chain ids
      std::string m_ChainIds;

      //! sequence exclusion
      size_t m_SequenceExclusion;

      //! radius of spheres for the overlapping spheres algorithm
      double m_Radius;

      //! whether to split statistics for each environment type
      bool m_SplitEnvironment;

    public:

      //! single instance of that class
      static const util::SiPtr< const util::ObjectInterface> s_Instance;
      static const util::SiPtr< const util::ObjectInterface> s_InstanceEnv;

    //////////////////////////////////
    // construction and destruction //
    //////////////////////////////////

      //! @brief default constructor
      OLS();

      //! @brief explicit constructor
      OLS( const bool SPLIT_ENVIRONMENT);

      //! @brief virtual copy constructor
      OLS *Clone() const;

    /////////////////
    // data access //
    /////////////////

      //! @brief returns class name
      //! @return the class name as constant reference to std::string
      const std::string &GetClassIdentifier() const;

      //! @brief gives the string to append to the the end of a filename to identify this analysis
      //! @return gives the string to append to the the end of a filename to identify this analysis
      const std::string &GetOutFilePostfix() const;

      //! @brief returns chain ids
      //! @return chain ids
      const std::string &GetChainIds() const;

      //! @brief returns the sequence exclusion considered when creating neighbor list
      //! @return the sequence exclusion considered when creating neighbor list
      const size_t &GetSequenceExclusion() const;

      //! @brief returns the radius for the overlapping spheres algorithm
      //! @reurn the radius for the overlapping spheres algorithm
      const double &GetRadius() const;

      //! @brief returns the name used for this class in an object data label
      //! @return the name used for this class in an object data label
      const std::string &GetAlias() const;

    ///////////////
    // operators //
    ///////////////

      //! @brief takes an ensemble and does an analysis resulting in string containing formatted information
      //! @param ENSEMBLE the protein ensemble that will be analyzed
      //! @return string which has the analyzed information about the ensemble
      std::string operator()( const assemble::ProteinEnsemble &ENSEMBLE) const;

    protected:

    //////////////////////
    // helper functions //
    //////////////////////

      //! @brief return parameters for member data that are set up from the labels
      //! @return parameters for member data that are set up from the labels
      io::Serializer GetSerializer() const;

    }; // end class OLS
  } // namespace scorestat
} // namespace bcl

#endif // BCL_SCORESTAT_OLS_H_