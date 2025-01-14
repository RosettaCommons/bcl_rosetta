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

#ifndef BCL_APP_CONFORMER_FROM_SCAFFOLD_H_
#define BCL_APP_CONFORMER_FROM_SCAFFOLD_H_

// include header of this class

// includes from bcl - sorted alphabetically
#include "app/bcl_app_apps.h"
#include "chemistry/bcl_chemistry_conformation_graph_converter.h"
#include "chemistry/bcl_chemistry_fragment_ensemble.h"
#include "command/bcl_command_app_default_flags.h"
#include "command/bcl_command_command.h"
#include "command/bcl_command_flag_static.h"
#include "command/bcl_command_parameter_check_file_existence.h"
#include "command/bcl_command_parameter_check_ranged.h"
#include "command/bcl_command_parameter_check_serializable.h"
#include "graph/bcl_graph_csi_substructure.h"
#include "io/bcl_io_file.h"
#include "sched/bcl_sched_scheduler_interface.h"
#include "sched/bcl_sched_thunk_job.h"
#include "storage/bcl_storage_template_instantiations.h"

namespace bcl
{
  namespace app
  {
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //!
    //! @class ConformerFromScaffold
    //! @brief Application for generating a 3D conformer starting from a fixed substructure
    //!
    //! @author brownbp1
    //! @date 12/16/2023
    //!
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class ConformerFromScaffold :
      public Interface
    {

    public:

      // static instance of this class
      static const ApplicationType ConformerFromScaffold_Instance;

    private:

    //////////
    // data //
    //////////

      ////// Command line flags ///////

      //! file containing the molecules for which new 3D conformers will be generated
      util::ShPtr< command::FlagInterface> m_InputFileFlag;

      //! file containing molecules against which substructure comparisons will be performed
      util::ShPtr< command::FlagInterface> m_ScaffoldFileFlag;

      //! output filename
      util::ShPtr< command::FlagInterface> m_OutputFileFlag;

      //! output filename for failed cases
      util::ShPtr< command::FlagInterface> m_OutputSimilarityFailureFileFlag;
      util::ShPtr< command::FlagInterface> m_OutputConfGenFailureFileFlag;

      //! mode for selecting which molecule(s) will be used to determine the base substructure
      //! (1) all
      //! (2) similarity
//      util::ShPtr< command::FlagInterface> m_ModeFlag;

      // atom comparison type
      util::ShPtr< command::FlagInterface> m_AtomTypeFlag;

      // bond comparison type
      util::ShPtr< command::FlagInterface> m_BondTypeFlag;

      //! minimum allowed size for the subgraph isomorphism
      util::ShPtr< command::FlagInterface> m_MinSizeFlag;

      // solution type for the isomorphism search
      util::ShPtr< command::FlagInterface> m_SolutionTypeFlag;

      // minimum similarity required or else molecule is a failure
      util::ShPtr< command::FlagInterface> m_SimilarityThresholdFlag;

      // if true, then follow the largest common substructure search with
      // a search for all subgraph isomorphisms between the common substructures;
      // this allows alternative poses to be discovered for symmetric molecules
      util::ShPtr< command::FlagInterface> m_FindAllFlag;

      // save only unique conformers from the final ensemble; only applicable if 'find_all' is enabled
      util::ShPtr< command::FlagInterface> m_UniqueFlag;

      // keep the ensemble of unique generated conformers; only applicable if 'find_all' is enabled; occurs after application of 'filter_metric'
      util::ShPtr< command::FlagInterface> m_SaveEnsembleFlag;

      ////// Convenience data for the app ///////

      mutable io::OFStream m_Output;
      mutable io::OFStream m_OutputSimilarityFailures;
      mutable io::OFStream m_OutputConfgenFailures;
      mutable size_t m_MoleculeIndex = 0;
      mutable size_t m_SuccessCount = 0;
      mutable size_t m_SimilarityFailureCount = 0;
      mutable size_t m_ConfgenFailureCount = 0;

    ///////////////////////////////////
    // construction and destruction //
    ///////////////////////////////////

      //! default constructor
      ConformerFromScaffold();

      //! copy constructor, only copy the flags
      ConformerFromScaffold( const ConformerFromScaffold &PARENT);

    public:

      //! @brief Clone function
      //! @return pointer to new ConformerFromScaffold
      ConformerFromScaffold *Clone() const;

    /////////////////
    // data access //
    /////////////////

      //! @brief returns class name of the object behind a pointer or the current object
      //! @return the class name
      const std::string &GetClassIdentifier() const;

      //! @brief initializes the command object for that executable
      util::ShPtr< command::Command> InitializeCommand() const;

      //! @brief the Main function
      //! @return error code - 0 for success
      int Main() const;

    private:

      void InitializeOutputFiles() const;

      util::Implementation< chemistry::ConformationComparisonInterface> InitializeSimilarityMetric() const;

      graph::CommonSubgraphIsomorphismBase::SolutionType InitializeSolutionType() const;

      chemistry::FragmentAlignToScaffold InitializeAlignmentObject( const graph::CommonSubgraphIsomorphismBase::SolutionType &SOLUTION_TYPE) const;

      storage::Pair< size_t, float> FindBestScaffoldBySimilarity
      (
        const chemistry::FragmentComplete &MOLECULE,
        const storage::Vector< chemistry::FragmentComplete> &SCAFFOLD_MOLECULES,
        const util::Implementation< chemistry::ConformationComparisonInterface> &SIMILARITY_METRIC
      ) const;

      chemistry::FragmentEnsemble Run
      (
        const chemistry::FragmentComplete &TARGET_MOLECULE,
        const chemistry::FragmentComplete &SCAFFOLD_MOLECULE,
        const chemistry::FragmentAlignToScaffold &ALIGNMENT_OBJECT,
        const descriptor::MoleculeSimilarity &ALIGNMENT_SCORER,
        const bool FIND_ALL = false
      ) const;

    //////////////////////
    // input and output //
    //////////////////////

    protected:

      //! @brief read from std::istream
      //! @param ISTREAM input stream
      //! @return istream which was read from
      std::istream &Read( std::istream &ISTREAM);

      //! @brief write to std::ostream
      //! @param OSTREAM output stream to write to
      //! @param INDENT number of indentations
      //! @return output stream which was written to
      std::ostream &Write( std::ostream &OSTREAM, const size_t INDENT) const;

    }; // ConformerFromScaffold

  } // namespace app
} // namespace bcl

#endif // BCL_APP_CONFORMER_FROM_SCAFFOLD_H_
