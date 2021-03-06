#ifndef AMREX_MLMGBNDRY_H_
#define AMREX_MLMGBNDRY_H_

#include <AMReX_InterpBndryData.H>
#include <AMReX_LO_BCTYPES.H>

namespace amrex {

class MLMGBndry
    :
    public InterpBndryData
{
public:

    using BCTuple = std::array<BoundCond,2*BL_SPACEDIM>;

    MLMGBndry (const BoxArray& _grids,
               const DistributionMapping& _dmap,
               int             _ncomp,
               const Geometry& _geom);

    virtual ~MLMGBndry ()  override;

    MLMGBndry (MLMGBndry&& rhs) = delete;
    MLMGBndry (const MLMGBndry& rhs) = delete;
    MLMGBndry& operator= (const MLMGBndry& rhs) = delete;
    MLMGBndry& operator= (MLMGBndry&& rhs) = delete;

    void setLOBndryConds (const std::array<LinOpBCType,AMREX_SPACEDIM>& lo,
                          const std::array<LinOpBCType,AMREX_SPACEDIM>& hi,
                          int ratio);

    static void setBoxBC (RealTuple& bloc, BCTuple& bctag, const Box& bx, const Box& domain,
                          const std::array<LinOpBCType,AMREX_SPACEDIM>& lo,
                          const std::array<LinOpBCType,AMREX_SPACEDIM>& hi,
                          const Real* dx, int ratio);
};

}

#endif
