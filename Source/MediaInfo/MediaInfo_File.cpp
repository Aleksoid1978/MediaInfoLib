/*  Copyright (c) MediaArea.net SARL. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license that can
 *  be found in the License.html file in the root of the source tree.
 */

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// How to:
// To add a new format,
// Fill includes, SelectFromExtension, ListFormats and LibraryIsModified
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
// Pre-compilation
#include "MediaInfo/PreComp.h"
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#define SAFE_DELETE(p) \
{\
    CS.Enter(); \
    delete p; \
    p=NULL; \
    CS.Leave(); \
}

//---------------------------------------------------------------------------
#include "MediaInfo/MediaInfo_Internal.h"
#include "MediaInfo/File__Analyze.h"
#include "MediaInfo/Reader/Reader_File.h"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Multiple
#if defined(MEDIAINFO_AAF_YES)
    #include "MediaInfo/Multiple/File_Aaf.h"
#endif
#if defined(MEDIAINFO_BDMV_YES)
    #include "MediaInfo/Multiple/File_Bdmv.h"
#endif
#if defined(MEDIAINFO_CDXA_YES)
    #include "MediaInfo/Multiple/File_Cdxa.h"
#endif
#if defined(MEDIAINFO_DASHMPD_YES)
    #include "MediaInfo/Multiple/File_DashMpd.h"
#endif
#if defined(MEDIAINFO_DCP_YES)
    #include "MediaInfo/Multiple/File_DcpAm.h"
#endif
#if defined(MEDIAINFO_DCP_YES)
    #include "MediaInfo/Multiple/File_DcpCpl.h"
#endif
#if defined(MEDIAINFO_DCP_YES)
    #include "MediaInfo/Multiple/File_DcpPkl.h"
#endif
#if defined(MEDIAINFO_DVDIF_YES)
    #include "MediaInfo/Multiple/File_DvDif.h"
#endif
#if defined(MEDIAINFO_DVDV_YES)
    #include "MediaInfo/Multiple/File_Dvdv.h"
#endif
#if defined(MEDIAINFO_DXW_YES)
    #include "MediaInfo/Multiple/File_Dxw.h"
#endif
#if defined(MEDIAINFO_FLV_YES)
    #include "MediaInfo/Multiple/File_Flv.h"
#endif
#if defined(MEDIAINFO_GXF_YES)
    #include "MediaInfo/Multiple/File_Gxf.h"
#endif
#if defined(MEDIAINFO_HDSF4M_YES)
    #include "MediaInfo/Multiple/File_HdsF4m.h"
#endif
#if defined(MEDIAINFO_HLS_YES)
    #include "MediaInfo/Multiple/File_Hls.h"
#endif
#if defined(MEDIAINFO_IBI_YES)
    #include "MediaInfo/Multiple/File_Ibi.h"
#endif
#if defined(MEDIAINFO_ISM_YES)
    #include "MediaInfo/Multiple/File_Ism.h"
#endif
#if defined(MEDIAINFO_IMF_YES)
    #include "MediaInfo/Multiple/File_ImfCpl.h"
#endif
#if defined(MEDIAINFO_IVF_YES)
    #include "MediaInfo/Multiple/File_Ivf.h"
#endif
#if defined(MEDIAINFO_LXF_YES)
    #include "MediaInfo/Multiple/File_Lxf.h"
#endif
#if defined(MEDIAINFO_MK_YES)
    #include "MediaInfo/Multiple/File_Mk.h"
#endif
#if defined(MEDIAINFO_MIXML_YES)
    #include "MediaInfo/Multiple/File_MiXml.h"
#endif
#if defined(MEDIAINFO_MPEG4_YES)
    #include "MediaInfo/Multiple/File_Mpeg4.h"
#endif
#if defined(MEDIAINFO_MPEG4_YES)
    #include "MediaInfo/Multiple/File_Mpeg4_TimeCode.h"
#endif
#if defined(MEDIAINFO_MPEGPS_YES)
    #include "MediaInfo/Multiple/File_MpegPs.h"
#endif
#if defined(MEDIAINFO_MPEGTS_YES) || defined(MEDIAINFO_BDAV_YES) || defined(MEDIAINFO_TSP_YES)
    #include "MediaInfo/Multiple/File_MpegTs.h"
#endif
#if defined(MEDIAINFO_MXF_YES)
    #include "MediaInfo/Multiple/File_Mxf.h"
#endif
#if defined(MEDIAINFO_NSV_YES)
    #include "MediaInfo/Multiple/File_Nsv.h"
#endif
#if defined(MEDIAINFO_NUT_YES)
    #include "MediaInfo/Multiple/File_Nut.h"
#endif
#if defined(MEDIAINFO_OGG_YES)
    #include "MediaInfo/Multiple/File_Ogg.h"
#endif
#if defined(MEDIAINFO_P2_YES)
    #include "MediaInfo/Multiple/File_P2_Clip.h"
#endif
#if defined(MEDIAINFO_PMP_YES)
    #include "MediaInfo/Multiple/File_Pmp.h"
#endif
#if defined(MEDIAINFO_PTX_YES)
    #include "MediaInfo/Multiple/File_Ptx.h"
#endif
#if defined(MEDIAINFO_RIFF_YES)
    #include "MediaInfo/Multiple/File_Riff.h"
#endif
#if defined(MEDIAINFO_RM_YES)
    #include "MediaInfo/Multiple/File_Rm.h"
#endif
#if defined(MEDIAINFO_SEQUENCEINFO_YES)
    #include "MediaInfo/Multiple/File_SequenceInfo.h"
#endif
#if defined(MEDIAINFO_SKM_YES)
    #include "MediaInfo/Multiple/File_Skm.h"
#endif
#if defined(MEDIAINFO_SWF_YES)
    #include "MediaInfo/Multiple/File_Swf.h"
#endif
#if defined(MEDIAINFO_WM_YES)
    #include "MediaInfo/Multiple/File_Wm.h"
#endif
#if defined(MEDIAINFO_WTV_YES)
    #include "MediaInfo/Multiple/File_Wtv.h"
#endif
#if defined(MEDIAINFO_XDCAM_YES)
    #include "MediaInfo/Multiple/File_Xdcam_Clip.h"
#endif
#if defined(MEDIAINFO_DPG_YES)
    #include "MediaInfo/Multiple/File_Dpg.h"
#endif

//---------------------------------------------------------------------------
// Video
#if defined(MEDIAINFO_AV1_YES)
    #include "MediaInfo/Video/File_Av1.h"
#endif
#if defined(MEDIAINFO_AVC_YES)
    #include "MediaInfo/Video/File_Avc.h"
#endif
#if defined(MEDIAINFO_AVSV_YES)
    #include "MediaInfo/Video/File_AvsV.h"
#endif
#if defined(MEDIAINFO_AVS3V_YES)
    #include "MediaInfo/Video/File_Avs3V.h"
#endif
#if defined(MEDIAINFO_DIRAC_YES)
    #include "MediaInfo/Video/File_Dirac.h"
#endif
#if defined(MEDIAINFO_FLIC_YES)
    #include "MediaInfo/Video/File_Flic.h"
#endif
#if defined(MEDIAINFO_H263_YES)
    #include "MediaInfo/Video/File_H263.h"
#endif
#if defined(MEDIAINFO_MXF_YES)
    #include "MediaInfo/Video/File_HdrVividMetadata.h"
#endif
#if defined(MEDIAINFO_HEVC_YES)
    #include "MediaInfo/Video/File_Hevc.h"
#endif
#if defined(MEDIAINFO_MPEG4V_YES)
    #include "MediaInfo/Video/File_Mpeg4v.h"
#endif
#if defined(MEDIAINFO_MPEGV_YES)
    #include "MediaInfo/Video/File_Mpegv.h"
#endif
#if defined(MEDIAINFO_VC1_YES)
    #include "MediaInfo/Video/File_Vc1.h"
#endif
#if defined(MEDIAINFO_VC3_YES)
    #include "MediaInfo/Video/File_Vc3.h"
#endif
#if defined(MEDIAINFO_Y4M_YES)
    #include "MediaInfo/Video/File_Y4m.h"
#endif

//---------------------------------------------------------------------------
// Audio
#if defined(MEDIAINFO_AAC_YES)
    #include "MediaInfo/Audio/File_Aac.h"
#endif
#if defined(MEDIAINFO_AC3_YES)
    #include "MediaInfo/Audio/File_Ac3.h"
#endif
#if defined(MEDIAINFO_AC4_YES)
    #include "MediaInfo/Audio/File_Ac4.h"
#endif
#if defined(MEDIAINFO_ADM_YES)
    #include "MediaInfo/Audio/File_Adm.h"
#endif
#if defined(MEDIAINFO_ALS_YES)
    #include "MediaInfo/Audio/File_Als.h"
#endif
#if defined(MEDIAINFO_AMR_YES)
    #include "MediaInfo/Audio/File_Amr.h"
#endif
#if defined(MEDIAINFO_AMV_YES)
    #include "MediaInfo/Audio/File_Amv.h"
#endif
#if defined(MEDIAINFO_APE_YES)
    #include "MediaInfo/Audio/File_Ape.h"
#endif
#if defined(MEDIAINFO_APTX100_YES)
    #include "MediaInfo/Audio/File_Aptx100.h"
#endif
#if defined(MEDIAINFO_AU_YES)
    #include "MediaInfo/Audio/File_Au.h"
#endif
#if defined(MEDIAINFO_CAF_YES)
    #include "MediaInfo/Audio/File_Caf.h"
#endif
#if defined(MEDIAINFO_DSF_YES)
    #include "MediaInfo/Audio/File_Dsf.h"
#endif
#if defined(MEDIAINFO_DSDIFF_YES)
    #include "MediaInfo/Audio/File_Dsdiff.h"
#endif
#if defined(MEDIAINFO_DTS_YES)
    #include "MediaInfo/Audio/File_Dts.h"
#endif
#if defined(MEDIAINFO_DTSUHD_YES)
    #include "MediaInfo/Audio/File_DtsUhd.h"
#endif
#if defined(MEDIAINFO_DAT_YES)
    #include "MediaInfo/Audio/File_Dat.h"
#endif
#if defined(MEDIAINFO_DOLBYE_YES)
    #include "MediaInfo/Audio/File_DolbyE.h"
#endif
#if defined(MEDIAINFO_FLAC_YES)
    #include "MediaInfo/Audio/File_Flac.h"
#endif
#if defined(MEDIAINFO_IAMF_YES)
    #include "MediaInfo/Audio/File_Iamf.h"
#endif
#if defined(MEDIAINFO_IT_YES)
    #include "MediaInfo/Audio/File_ImpulseTracker.h"
#endif
#if defined(MEDIAINFO_LA_YES)
    #include "MediaInfo/Audio/File_La.h"
#endif
#if defined(MEDIAINFO_MIDI_YES)
    #include "MediaInfo/Audio/File_Midi.h"
#endif
#if defined(MEDIAINFO_MOD_YES)
    #include "MediaInfo/Audio/File_Module.h"
#endif
#if defined(MEDIAINFO_MPC_YES)
    #include "MediaInfo/Audio/File_Mpc.h"
#endif
#if defined(MEDIAINFO_MPCSV8_YES)
    #include "MediaInfo/Audio/File_MpcSv8.h"
#endif
#if defined(MEDIAINFO_MPEGA_YES)
    #include "MediaInfo/Audio/File_Mpega.h"
#endif
#if defined(MEDIAINFO_OPENMG_YES)
    #include "MediaInfo/Audio/File_OpenMG.h"
#endif
#if defined(MEDIAINFO_RKAU_YES)
    #include "MediaInfo/Audio/File_Rkau.h"
#endif
#if defined(MEDIAINFO_S3M_YES)
    #include "MediaInfo/Audio/File_ScreamTracker3.h"
#endif
#if defined(MEDIAINFO_SMPTEST0337_YES)
    #include "MediaInfo/Audio/File_SmpteSt0337.h"
#endif
#if defined(MEDIAINFO_TAK_YES)
    #include "MediaInfo/Audio/File_Tak.h"
#endif
#if defined(MEDIAINFO_TTA_YES)
    #include "MediaInfo/Audio/File_Tta.h"
#endif
#if defined(MEDIAINFO_TWINVQ_YES)
    #include "MediaInfo/Audio/File_TwinVQ.h"
#endif
#if defined(MEDIAINFO_WVPK_YES)
    #include "MediaInfo/Audio/File_Wvpk.h"
#endif
#if defined(MEDIAINFO_XM_YES)
    #include "MediaInfo/Audio/File_ExtendedModule.h"
#endif

//---------------------------------------------------------------------------
// Text
#if defined(MEDIAINFO_EIA608_YES)
    #include "MediaInfo/Text/File_Eia608.h"
#endif
#if defined(MEDIAINFO_CDP_YES)
    #include "MediaInfo/Text/File_Cdp.h"
#endif
#if defined(MEDIAINFO_N19_YES)
    #include "MediaInfo/Text/File_N19.h"
#endif
#if defined(MEDIAINFO_PAC_YES)
    #include "MediaInfo/Text/File_Pac.h"
#endif
#if defined(MEDIAINFO_PDF_YES)
    #include "MediaInfo/Text/File_Pdf.h"
#endif
#if defined(MEDIAINFO_SCC_YES)
    #include "MediaInfo/Text/File_Scc.h"
#endif
#if defined(MEDIAINFO_SDP_YES)
    #include "MediaInfo/Text/File_Sdp.h"
#endif
#if defined(MEDIAINFO_SUBRIP_YES)
    #include "MediaInfo/Text/File_SubRip.h"
#endif
#if defined(MEDIAINFO_TELETEXT_YES)
    #include "MediaInfo/Text/File_Teletext.h"
#endif
#if defined(MEDIAINFO_TTML_YES)
    #include "MediaInfo/Text/File_Ttml.h"
#endif
#if defined(MEDIAINFO_OTHERTEXT_YES)
    #include "MediaInfo/Text/File_OtherText.h"
#endif

//---------------------------------------------------------------------------
// Image
#if defined(MEDIAINFO_ARRIRAW_YES)
    #include "MediaInfo/Image/File_ArriRaw.h"
#endif
#if defined(MEDIAINFO_BMP_YES)
    #include "MediaInfo/Image/File_Bmp.h"
#endif
#if defined(MEDIAINFO_BPG_YES)
    #include "MediaInfo/Image/File_Bpg.h"
#endif
#if defined(MEDIAINFO_DDS_YES)
    #include "MediaInfo/Image/File_Dds.h"
#endif
#if defined(MEDIAINFO_DPX_YES)
    #include "MediaInfo/Image/File_Dpx.h"
#endif
#if defined(MEDIAINFO_EXR_YES)
    #include "MediaInfo/Image/File_Exr.h"
#endif
#if defined(MEDIAINFO_GIF_YES)
    #include "MediaInfo/Image/File_Gif.h"
#endif
#if defined(MEDIAINFO_ICO_YES)
    #include "MediaInfo/Image/File_Ico.h"
#endif
#if defined(MEDIAINFO_JPEG_YES)
    #include "MediaInfo/Image/File_Jpeg.h"
#endif
#if defined(MEDIAINFO_PCX_YES)
    #include "MediaInfo/Image/File_Pcx.h"
#endif
#if defined(MEDIAINFO_PNG_YES)
    #include "MediaInfo/Image/File_Png.h"
#endif
#if defined(MEDIAINFO_PSD_YES)
    #include "MediaInfo/Image/File_Psd.h"
#endif
#if defined(MEDIAINFO_TIFF_YES)
    #include "MediaInfo/Image/File_Tiff.h"
#endif
#if defined(MEDIAINFO_TGA_YES)
    #include "MediaInfo/Image/File_Tga.h"
#endif
#if defined(MEDIAINFO_WEBP_YES)
    #include "MediaInfo/Image/File_WebP.h"
#endif

//---------------------------------------------------------------------------
// Tag
#if defined(MEDIAINFO_C2PA_YES)
    #include "MediaInfo/Tag/File_C2pa.h"
#endif
#if defined(MEDIAINFO_ICC_YES)
    #include "MediaInfo/Tag/File_Icc.h"
#endif
#if defined(MEDIAINFO_SPHERICALVIDEO_YES)
    #include "MediaInfo/Tag/File_SphericalVideo.h"
#endif
#if defined(MEDIAINFO_XMP_YES)
    #include "MediaInfo/Tag/File_Xmp.h"
#endif

//---------------------------------------------------------------------------
// Archive
#if defined(MEDIAINFO_7Z_YES)
    #include "MediaInfo/Archive/File_7z.h"
#endif
#if defined(MEDIAINFO_ACE_YES)
    #include "MediaInfo/Archive/File_Ace.h"
#endif
#if defined(MEDIAINFO_BZIP2_YES)
    #include "MediaInfo/Archive/File_Bzip2.h"
#endif
#if defined(MEDIAINFO_ELF_YES)
    #include "MediaInfo/Archive/File_Elf.h"
#endif
#if defined(MEDIAINFO_GZIP_YES)
    #include "MediaInfo/Archive/File_Gzip.h"
#endif
#if defined(MEDIAINFO_ISO9660_YES)
    #include "MediaInfo/Archive/File_Iso9660.h"
#endif
#if defined(MEDIAINFO_MACHO_YES)
    #include "MediaInfo/Archive/File_MachO.h"
#endif
#if defined(MEDIAINFO_MZ_YES)
    #include "MediaInfo/Archive/File_Mz.h"
#endif
#if defined(MEDIAINFO_RAR_YES)
    #include "MediaInfo/Archive/File_Rar.h"
#endif
#if defined(MEDIAINFO_TAR_YES)
    #include "MediaInfo/Archive/File_Tar.h"
#endif
#if defined(MEDIAINFO_ZIP_YES)
    #include "MediaInfo/Archive/File_Zip.h"
#endif

//---------------------------------------------------------------------------
// Other
#if defined(MEDIAINFO_OTHER_YES)
    #include "MediaInfo/File_Other.h"
#endif
#if defined(MEDIAINFO_UNKNOWN_YES)
    #include "MediaInfo/File_Unknown.h"
#endif
#if defined(MEDIAINFO_DUMMY_YES)
    #include "MediaInfo/File_Dummy.h"
#endif
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//---------------------------------------------------------------------------
extern MediaInfo_Config Config;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
static File__Analyze* SelectFromExtension(const String& Parser)
{
    // Multiple
    #if defined(MEDIAINFO_AAF_YES)
        if (Parser==__T("Aaf"))        return new File_Aaf();
    #endif
    #if defined(MEDIAINFO_ADM_YES)
        if (Parser==__T("Adm"))        return new File_Adm();
    #endif
    #if defined(MEDIAINFO_BDAV_YES)
        if (Parser==__T("Bdav"))       {auto Parser=new File_MpegTs(); Parser->BDAV_Size=4; return Parser;}
    #endif
    #if defined(MEDIAINFO_BDMV_YES)
        if (Parser==__T("Bdmv"))        return new File_Bdmv();
    #endif
    #if defined(MEDIAINFO_CDXA_YES)
        if (Parser==__T("Cdxa"))        return new File_Cdxa();
    #endif
    #if defined(MEDIAINFO_DASHMPD_YES)
        if (Parser==__T("DashMpd"))     return new File_DashMpd();
    #endif
    #if defined(MEDIAINFO_DCP_YES)
        if (Parser==__T("DcpAm"))       return new File_DcpAm();
    #endif
    #if defined(MEDIAINFO_DCP_YES)
        if (Parser==__T("DcpCpl"))      return new File_DcpCpl();
    #endif
    #if defined(MEDIAINFO_DCP_YES)
        if (Parser==__T("DcpPkg"))      return new File_DcpPkl();
    #endif
    #if defined(MEDIAINFO_DPG_YES)
        if (Parser==__T("Dpg"))         return new File_Dpg();
    #endif
    #if defined(MEDIAINFO_DVDIF_YES)
        if (Parser==__T("DvDif"))        return new File_DvDif();
    #endif
    #if defined(MEDIAINFO_DVDV_YES)
        if (Parser==__T("Dvdv"))        return new File_Dvdv();
    #endif
    #if defined(MEDIAINFO_DXW_YES)
        if (Parser==__T("Dxw"))         return new File_Dxw();
    #endif
    #if defined(MEDIAINFO_FLV_YES)
        if (Parser==__T("Flv"))         return new File_Flv();
    #endif
    #if defined(MEDIAINFO_GXF_YES)
        if (Parser==__T("Gxf"))         return new File_Gxf();
    #endif
    #if defined(MEDIAINFO_HDSF4M_YES)
        if (Parser==__T("HdsF4m"))      return new File_HdsF4m();
    #endif
    #if defined(MEDIAINFO_HLS_YES)
        if (Parser==__T("Hls"))         return new File_Hls();
    #endif
    #if defined(MEDIAINFO_ISM_YES)
        if (Parser==__T("Ism"))         return new File_Ism();
    #endif
    #if defined(MEDIAINFO_IVF_YES)
        if (Parser==__T("Ivf"))         return new File_Ivf();
    #endif
    #if defined(MEDIAINFO_LXF_YES)
        if (Parser==__T("Lxf"))         return new File_Lxf();
    #endif
    #if defined(MEDIAINFO_MIXML_YES)
        if (Parser==__T("MiXml"))       return new File_MiXml();
    #endif
    #if defined(MEDIAINFO_MK_YES)
        if (Parser==__T("Mk"))          return new File_Mk();
    #endif
    #if defined(MEDIAINFO_MPEG4_YES)
        if (Parser==__T("Mpeg4"))       return new File_Mpeg4();
    #endif
    #if defined(MEDIAINFO_MPEG4_YES)
        if (Parser==__T("QuickTimeTC")) return new File_Mpeg4_TimeCode();
    #endif
    #if defined(MEDIAINFO_MPEGPS_YES)
        if (Parser==__T("MpegPs"))      return new File_MpegPs();
    #endif
    #if defined(MEDIAINFO_MPEGTS_YES)
        if (Parser==__T("MpegTs"))      return new File_MpegTs();
    #endif
    #if defined(MEDIAINFO_MXF_YES)
        if (Parser==__T("Mxf"))         return new File_Mxf();
    #endif
    #if defined(MEDIAINFO_NSV_YES)
        if (Parser==__T("Nsv"))         return new File_Nsv();
    #endif
    #if defined(MEDIAINFO_NUT_YES)
        if (Parser==__T("Nut"))         return new File_Nut();
    #endif
    #if defined(MEDIAINFO_OGG_YES)
        if (Parser==__T("Ogg"))         return new File_Ogg();
    #endif
    #if defined(MEDIAINFO_P2_YES)
        if (Parser==__T("P2_Clip"))     return new File_P2_Clip();
    #endif
    #if defined(MEDIAINFO_PMP_YES)
        if (Parser==__T("Pmp"))         return new File_Pmp();
    #endif
    #if defined(MEDIAINFO_PTX_YES)
        if (Parser==__T("Ptx"))         return new File_Ptx();
    #endif
    #if defined(MEDIAINFO_RIFF_YES)
        if (Parser==__T("Riff"))        return new File_Riff();
    #endif
    #if defined(MEDIAINFO_RM_YES)
        if (Parser==__T("Rm"))          return new File_Rm();
    #endif
    #if defined(MEDIAINFO_SEQUENCEINFO_YES)
        if (Parser==__T("SequenceInfo")) return new File_SequenceInfo();
    #endif
    #if defined(MEDIAINFO_SKM_YES)
        if (Parser==__T("Skm"))         return new File_Skm();
    #endif
    #if defined(MEDIAINFO_SWF_YES)
        if (Parser==__T("Swf"))         return new File_Swf();
    #endif
    #if defined(MEDIAINFO_WM_YES)
        if (Parser==__T("Wm"))          return new File_Wm();
    #endif
    #if defined(MEDIAINFO_WTV_YES)
        if (Parser==__T("Wtv"))         return new File_Wtv();
    #endif
    #if defined(MEDIAINFO_XDCAM_YES)
        if (Parser==__T("Xdcam_Clip"))   return new File_Xdcam_Clip();
    #endif

    // Video
    #if defined(MEDIAINFO_AV1_YES)
        if (Parser==__T("Av1"))         return new File_Av1();
    #endif
    #if defined(MEDIAINFO_AVC_YES)
        if (Parser==__T("Avc"))         return new File_Avc();
    #endif
    #if defined(MEDIAINFO_HEVC_YES)
        if (Parser==__T("Hevc"))         return new File_Hevc();
    #endif
    #if defined(MEDIAINFO_AVSV_YES)
        if (Parser==__T("AvsV"))        return new File_AvsV();
    #endif
    #if defined(MEDIAINFO_AVS3V_YES)
        if (Parser==__T("Avs3V"))       return new File_Avs3V();
    #endif
    #if defined(MEDIAINFO_DIRAC_YES)
        if (Parser==__T("Dirac"))       return new File_Dirac();
    #endif
    #if defined(MEDIAINFO_FLIC_YES)
        if (Parser==__T("Flic"))        return new File_Flic();
    #endif
    #if defined(MEDIAINFO_H263_YES)
        if (Parser==__T("H263"))        return new File_H263();
    #endif
    #if defined(MEDIAINFO_MPEG4V_YES)
        if (Parser==__T("Mpeg4v"))      return new File_Mpeg4v();
    #endif
    #if defined(MEDIAINFO_MPEGV_YES)
        if (Parser==__T("Mpegv"))       return new File_Mpegv();
    #endif
    #if defined(MEDIAINFO_VC1_YES)
        if (Parser==__T("Vc1"))         return new File_Vc1();
    #endif
    #if defined(MEDIAINFO_VC3_YES)
        if (Parser==__T("Vc3"))         return new File_Vc3();
    #endif
    #if defined(MEDIAINFO_Y4M_YES)
        if (Parser==__T("Y4m"))         return new File_Y4m();
    #endif

    // Audio
    #if defined(MEDIAINFO_AAC_YES)
        if (Parser==__T("Adts"))       {auto Parser=new File_Aac(); Parser->Mode=File_Aac::Mode_ADTS; return Parser;} // Prioritization against ADIF
    #endif
    #if defined(MEDIAINFO_AC3_YES)
        if (Parser==__T("Ac3"))         return new File_Ac3();
    #endif
    #if defined(MEDIAINFO_AC4_YES)
        if (Parser==__T("Ac4"))         return new File_Ac4();
    #endif
    #if defined(MEDIAINFO_SMPTEST0337_YES)
        if (Parser==__T("Aes3"))        return new File_SmpteSt0337();
    #endif
    #if defined(MEDIAINFO_ALS_YES)
        if (Parser==__T("Als"))         return new File_Als();
    #endif
    #if defined(MEDIAINFO_AMR_YES)
        if (Parser==__T("Amr"))         return new File_Amr();
    #endif
    #if defined(MEDIAINFO_AMV_YES)
        if (Parser==__T("Amv"))         return new File_Amv();
    #endif
    #if defined(MEDIAINFO_APE_YES)
        if (Parser==__T("Ape"))         return new File_Ape();
    #endif
    #if defined(MEDIAINFO_APTX100_YES)
        if (Parser==__T("Aptx100"))     return new File_Aptx100();
    #endif
    #if defined(MEDIAINFO_AU_YES)
        if (Parser==__T("Au"))          return new File_Au();
    #endif
    #if defined(MEDIAINFO_CAF_YES)
        if (Parser==__T("Caf"))          return new File_Caf();
    #endif
    #if defined(MEDIAINFO_DSF_YES)
        if (Parser==__T("Dsf"))         return new File_Dsf();
    #endif
    #if defined(MEDIAINFO_DTS_YES)
        if (Parser==__T("Dsdiff"))      return new File_Dsdiff();
    #endif
    #if defined(MEDIAINFO_DTS_YES)
        if (Parser==__T("Dts"))         return new File_Dts();
    #endif
    #if defined(MEDIAINFO_DTSUHD_YES)
        if (Parser==__T("DtsUhd"))      return new File_DtsUhd();
    #endif
    #if defined(MEDIAINFO_DAT_YES)
        if (Parser==__T("Dat"))        return new File_Dat();
    #endif
    #if defined(MEDIAINFO_DOLBYE_YES)
        if (Parser==__T("DolbyE"))      return new File_DolbyE();
    #endif
    #if defined(MEDIAINFO_FLAC_YES)
        if (Parser==__T("Flac"))        return new File_Flac();
    #endif
    #if defined(MEDIAINFO_IAMF_YES)
        if (Parser == __T("Iamf"))      return new File_Iamf();
    #endif
    #if defined(MEDIAINFO_IT_YES)
        if (Parser==__T("It"))          return new File_ImpulseTracker();
    #endif
    #if defined(MEDIAINFO_LA_YES)
        if (Parser==__T("La"))          return new File_La();
    #endif
    #if defined(MEDIAINFO_MIDI_YES)
        if (Parser==__T("Midi"))        return new File_Midi();
    #endif
    #if defined(MEDIAINFO_MOD_YES)
        if (Parser==__T("Mod"))         return new File_Module();
    #endif
    #if defined(MEDIAINFO_MPC_YES)
        if (Parser==__T("Mpc"))         return new File_Mpc();
    #endif
    #if defined(MEDIAINFO_MPCSV8_YES)
        if (Parser==__T("MpcSv8"))      return new File_MpcSv8();
    #endif
    #if defined(MEDIAINFO_MPEGA_YES)
        if (Parser==__T("Mpega"))       return new File_Mpega();
    #endif
    #if defined(MEDIAINFO_OPENMG_YES)
        if (Parser==__T("OpenMG"))      return new File_OpenMG();
    #endif
    #if defined(MEDIAINFO_RKAU_YES)
        if (Parser==__T("Rkau"))        return new File_Rkau();
    #endif
    #if defined(MEDIAINFO_S3M_YES)
        if (Parser==__T("S3m"))         return new File_ScreamTracker3();
    #endif
    #if defined(MEDIAINFO_TAK_YES)
        if (Parser==__T("Tak"))         return new File_Tak();
    #endif
    #if defined(MEDIAINFO_TTA_YES)
        if (Parser==__T("Tta"))         return new File_Tta();
    #endif
    #if defined(MEDIAINFO_TWINVQ_YES)
        if (Parser==__T("TwinVQ"))      return new File_TwinVQ();
    #endif
    #if defined(MEDIAINFO_WVPK_YES)
        if (Parser==__T("Wvpk"))        return new File_Wvpk();
    #endif
    #if defined(MEDIAINFO_XM_YES)
        if (Parser==__T("Xm"))          return new File_ExtendedModule();
    #endif

    // Text
    #if defined(MEDIAINFO_EIA608_YES)
        if (Parser==__T("CEA-608"))     return new File_Eia608();
        if (Parser==__T("EIA-608"))     return new File_Eia608();
    #endif
    #if defined(MEDIAINFO_CDP_YES)
        if (Parser==__T("CDP"))         return new File_Cdp();
    #endif
    #if defined(MEDIAINFO_N19_YES)
        if (Parser==__T("N19"))         return new File_N19();
    #endif
    #if defined(MEDIAINFO_PAC_YES)
        if (Parser==__T("PAC"))         return new File_Pac();
    #endif
    #if defined(MEDIAINFO_PDF_YES)
        if (Parser==__T("PDF"))         return new File_Pdf();
    #endif
    #if defined(MEDIAINFO_SCC_YES)
        if (Parser==__T("SCC"))         return new File_Scc();
    #endif
    #if defined(MEDIAINFO_SDP_YES)
        if (Parser==__T("SDP"))         return new File_Sdp();
    #endif
    #if defined(MEDIAINFO_SUBRIP_YES)
        if (Parser==__T("SubRip"))      return new File_SubRip();
        if (Parser==__T("WebVTT"))      return new File_SubRip();
    #endif
    #if defined(MEDIAINFO_TELETEXT_YES)
        if (Parser==__T("Teletext"))    return new File_Teletext();
    #endif
    #if defined(MEDIAINFO_TTML_YES)
        if (Parser==__T("TTML"))        return new File_Ttml();
    #endif
    #if defined(MEDIAINFO_OTHERTEXT_YES)
        if (Parser==__T("OtherText"))   return new File_OtherText();
    #endif

    // Image
    #if defined(MEDIAINFO_ARRIRAW_YES)
        if (Parser==__T("Arri Raw"))    return new File_ArriRaw();
    #endif
    #if defined(MEDIAINFO_BMP_YES)
        if (Parser==__T("Bmp"))         return new File_Bmp();
    #endif
    #if defined(MEDIAINFO_BPG_YES)
        if (Parser==__T("Bpg"))         return new File_Bpg();
    #endif
    #if defined(MEDIAINFO_DDS_YES)
        if (Parser==__T("Dds"))         return new File_Dds();
    #endif
    #if defined(MEDIAINFO_DPX_YES)
        if (Parser==__T("Dpx"))         return new File_Dpx();
    #endif
    #if defined(MEDIAINFO_EXR_YES)
        if (Parser==__T("Exr"))         return new File_Exr();
    #endif
    #if defined(MEDIAINFO_GIF_YES)
        if (Parser==__T("Gif"))         return new File_Gif();
    #endif
    #if defined(MEDIAINFO_ICO_YES)
        if (Parser==__T("Ico"))         return new File_Ico();
    #endif
    #if defined(MEDIAINFO_JPEG_YES)
        if (Parser==__T("Jpeg"))        return new File_Jpeg();
    #endif
    #if defined(MEDIAINFO_PCX_YES)
        if (Parser==__T("PCX"))         return new File_Pcx();
    #endif
    #if defined(MEDIAINFO_PNG_YES)
        if (Parser==__T("Png"))         return new File_Png();
    #endif
    #if defined(MEDIAINFO_PSD_YES)
        if (Parser==__T("Psd"))         return new File_Psd();
    #endif
    #if defined(MEDIAINFO_TIFF_YES)
        if (Parser==__T("Tiff"))        return new File_Tiff();
    #endif
    #if defined(MEDIAINFO_TGA_YES)
        if (Parser==__T("Tga"))         return new File_Tga();
    #endif
    #if defined(MEDIAINFO_WEBP_YES)
        if (Parser==__T("WebP"))        return new File_WebP();
    #endif

    // Tags
    #if defined(MEDIAINFO_C2PA_YES)
        if (Parser==__T("C2pa"))        return new File_C2pa();
    #endif
    #if defined(MEDIAINFO_ICC_YES)
        if (Parser==__T("Icc"))          return new File_Icc();
    #endif

    // Archive
    #if defined(MEDIAINFO_7Z_YES)
        if (Parser==__T("7z"))          return new File_7z();
    #endif
    #if defined(MEDIAINFO_ACE_YES)
        if (Parser==__T("Ace"))         return new File_Ace();
    #endif
    #if defined(MEDIAINFO_BZIP2_YES)
        if (Parser==__T("Bzip2"))       return new File_Bzip2();
    #endif
    #if defined(MEDIAINFO_ELF_YES)
        if (Parser==__T("Elf"))         return new File_Elf();
    #endif
    #if defined(MEDIAINFO_GZIP_YES)
        if (Parser==__T("Gzip"))        return new File_Gzip();
    #endif
    #if defined(MEDIAINFO_ISO9660_YES)
        if (Parser==__T("Iso9660"))     return new File_Iso9660();
    #endif
    #if defined(MEDIAINFO_MZ_YES)
        if (Parser==__T("Mz"))          return new File_Mz();
    #endif
    #if defined(MEDIAINFO_MACHO_YES)
        if (Parser==__T("MachO"))       return new File_MachO();
    #endif
    #if defined(MEDIAINFO_RAR_YES)
        if (Parser==__T("Rar"))         return new File_Rar();
    #endif
    #if defined(MEDIAINFO_TAR_YES)
        if (Parser==__T("Tar"))         return new File_Tar();
    #endif
    #if defined(MEDIAINFO_ZIP_YES)
        if (Parser==__T("Zip"))         return new File_Zip();
    #endif

    // Other
    #if defined(MEDIAINFO_OTHER_YES)
        if (Parser==__T("Other"))       return new File_Other();
    #endif

    //No parser
    return nullptr;
}

//---------------------------------------------------------------------------
bool MediaInfo_Internal::SelectFromExtension (const String &Parser)
{
    CriticalSectionLocker CSL(CS);

    //Clear last value
    delete Info; Info=NULL;

    //Searching the right File_*
    Info=MediaInfoLib::SelectFromExtension(Parser);
    return Info?true:false;
}

//---------------------------------------------------------------------------
#if defined(MEDIAINFO_FILE_YES)
int MediaInfo_Internal::ListFormats(const String &File_Name)
{
    // Multiple
    #if defined(MEDIAINFO_AAF_YES)
        SAFE_DELETE(Info); Info=new File_Aaf();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_BDAV_YES)
        SAFE_DELETE(Info); Info=new File_MpegTs(); ((File_MpegTs*)Info)->BDAV_Size=4; if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
        SAFE_DELETE(Info); Info=new File_MpegTs(); ((File_MpegTs*)Info)->BDAV_Size=4; ((File_MpegTs*)Info)->NoPatPmt=true; if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_BDMV_YES)
        SAFE_DELETE(Info); Info=new File_Bdmv();               if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_CDXA_YES)
        SAFE_DELETE(Info); Info=new File_Cdxa();               if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_DASHMPD_YES)
        SAFE_DELETE(Info); Info=new File_DashMpd();            if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_DCP_YES)
        SAFE_DELETE(Info); Info=new File_DcpAm();              if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_DCP_YES)
        SAFE_DELETE(Info); Info=new File_DcpCpl();             if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_DCP_YES)
        SAFE_DELETE(Info); Info=new File_DcpPkl();             if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_DVDIF_YES)
        SAFE_DELETE(Info); Info=new File_DvDif();              if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_DVDV_YES)
        SAFE_DELETE(Info); Info=new File_Dvdv();               if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_DXW_YES)
        SAFE_DELETE(Info); Info=new File_Dxw();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_FLV_YES)
        SAFE_DELETE(Info); Info=new File_Flv();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_GXF_YES)
        SAFE_DELETE(Info); Info=new File_Gxf();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_HDSF4M_YES)
        SAFE_DELETE(Info); Info=new File_HdsF4m();             if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_HLS_YES)
        SAFE_DELETE(Info); Info=new File_Hls();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_IBI_YES)
        SAFE_DELETE(Info); Info=new File_Ibi();                 if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_ISM_YES)
        SAFE_DELETE(Info); Info=new File_Ism();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_IVF_YES)
        SAFE_DELETE(Info); Info=new File_Ivf();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_LXF_YES)
        SAFE_DELETE(Info); Info=new File_Lxf();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_MK_YES)
        SAFE_DELETE(Info); Info=new File_Mk();                 if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_MIXML_YES)
        SAFE_DELETE(Info); Info=new File_MiXml();              if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_MPEG4_YES)
        SAFE_DELETE(Info); Info=new File_Mpeg4();              if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_MPEGPS_YES)
        SAFE_DELETE(Info); Info=new File_MpegPs();             if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_MPEGTS_YES)
        SAFE_DELETE(Info); Info=new File_MpegTs();             if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
        SAFE_DELETE(Info); Info=new File_MpegTs(); ((File_MpegTs*)Info)->NoPatPmt=true; if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_MPLI_YES)
        SAFE_DELETE(Info); Info=new File_Mpli();               if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_MXF_YES)
        SAFE_DELETE(Info); Info=new File_Mxf();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_NSV_YES)
        SAFE_DELETE(Info); Info=new File_Nsv();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_NUT_YES)
        SAFE_DELETE(Info); Info=new File_Nut();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_OGG_YES)
        SAFE_DELETE(Info); Info=new File_Ogg();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_P2_YES)
        SAFE_DELETE(Info); Info=new File_P2_Clip();            if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_PMP_YES)
        SAFE_DELETE(Info); Info=new File_Pmp();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_PTX_YES)
        SAFE_DELETE(Info); Info=new File_Ptx();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_RIFF_YES)
        SAFE_DELETE(Info); Info=new File_Riff();               if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_RM_YES)
        SAFE_DELETE(Info); Info=new File_Rm();                 if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_SEQUENCEINFO_YES)
        SAFE_DELETE(Info); Info=new File_SequenceInfo();       if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_SKM_YES)
        SAFE_DELETE(Info); Info=new File_Skm();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_SWF_YES)
        SAFE_DELETE(Info); Info=new File_Swf();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_TSP_YES)
        SAFE_DELETE(Info); Info=new File_MpegTs(); ((File_MpegTs*)Info)->TSP_Size=16; if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
        SAFE_DELETE(Info); Info=new File_MpegTs(); ((File_MpegTs*)Info)->TSP_Size=16; ((File_MpegTs*)Info)->NoPatPmt=true; if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_WM_YES)
        SAFE_DELETE(Info); Info=new File_Wm();                 if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_WTV_YES)
        SAFE_DELETE(Info); Info=new File_Wtv();                 if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_XDCAM_YES)
        SAFE_DELETE(Info); Info=new File_Xdcam_Clip();         if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_DPG_YES)
        SAFE_DELETE(Info); Info=new File_Dpg();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif

    // Video
    #if defined(MEDIAINFO_AV1_YES)
        SAFE_DELETE(Info); Info=new File_Av1();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_AVC_YES)
        SAFE_DELETE(Info); Info=new File_Avc();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_MXF_YES)
        SAFE_DELETE(Info); Info = new File_HdrVividMetadata(); if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name) > 0) return 1;
    #endif
    #if defined(MEDIAINFO_HEVC_YES)
        SAFE_DELETE(Info); Info=new File_Hevc();               if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_AVSV_YES)
        SAFE_DELETE(Info); Info=new File_AvsV();               if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_AVS3V_YES)
        SAFE_DELETE(Info); Info=new File_Avs3V();              if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_DIRAC_YES)
        SAFE_DELETE(Info); Info=new File_Dirac();              if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_FLIC_YES)
        SAFE_DELETE(Info); Info=new File_Flic();               if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_H263_YES)
        //SAFE_DELETE(Info); Info=new File_H263();               if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1; //At the end, too much sensible
    #endif
    #if defined(MEDIAINFO_MPEG4V_YES)
        SAFE_DELETE(Info); Info=new File_Mpeg4v();             if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_MPEGV_YES)
        SAFE_DELETE(Info); Info=new File_Mpegv();              if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_VC1_YES)
        SAFE_DELETE(Info); Info=new File_Vc1();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_VC3_YES)
        SAFE_DELETE(Info); Info=new File_Vc3();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_Y4M_YES)
        SAFE_DELETE(Info); Info=new File_Y4m();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif

    // Audio
    #if defined(MEDIAINFO_AAC_YES)
        SAFE_DELETE(Info); Info=new File_Aac();               if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_AC3_YES)
        SAFE_DELETE(Info); Info=new File_Ac3();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_AC4_YES)
        SAFE_DELETE(Info); Info=new File_Ac4();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_SMPTEST0337_YES)
        SAFE_DELETE(Info); Info=new File_SmpteSt0337();        if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_ALS_YES)
        SAFE_DELETE(Info); Info=new File_Als();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_AMR_YES)
        SAFE_DELETE(Info); Info=new File_Amr();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_AMV_YES)
        SAFE_DELETE(Info); Info=new File_Amv();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_APE_YES)
        SAFE_DELETE(Info); Info=new File_Ape();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_APTX100_YES)
        SAFE_DELETE(Info); Info=new File_Aptx100();            if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_AU_YES)
        SAFE_DELETE(Info); Info=new File_Au();                 if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_CAF_YES)
        SAFE_DELETE(Info); Info=new File_Caf();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_DSF_YES)
        SAFE_DELETE(Info); Info=new File_Dsf();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_DSDIFF_YES)
        SAFE_DELETE(Info); Info=new File_Dsdiff();             if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_DTS_YES)
        SAFE_DELETE(Info); Info=new File_Dts();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_DTSUHD_YES)
        SAFE_DELETE(Info); Info=new File_DtsUhd();             if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_DAT_YES)
        SAFE_DELETE(Info); Info=new File_Dat();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
//    Too many false-positives
//    #if defined(MEDIAINFO_DOLBYE_YES)
//       SAFE_DELETE(Info); Info=new File_DolbyE();             if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
//    #endif
    #if defined(MEDIAINFO_FLAC_YES)
        SAFE_DELETE(Info); Info=new File_Flac();               if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_IAMF_YES)
        SAFE_DELETE(Info); Info=new File_Iamf();               if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_IT_YES)
        SAFE_DELETE(Info); Info=new File_ImpulseTracker();     if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_LA_YES)
        SAFE_DELETE(Info); Info=new File_La();                 if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_MIDI_YES)
        SAFE_DELETE(Info); Info=new File_Midi();               if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_MOD_YES)
        SAFE_DELETE(Info); Info=new File_Module();             if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_MPC_YES)
        SAFE_DELETE(Info); Info=new File_Mpc();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_MPCSV8_YES)
        SAFE_DELETE(Info); Info=new File_MpcSv8();             if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_OPENMG_YES)
        SAFE_DELETE(Info); Info=new File_OpenMG();             if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_RKAU_YES)
        SAFE_DELETE(Info); Info=new File_Rkau();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_TAK_YES)
        SAFE_DELETE(Info); Info=new File_Tak();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_S3M_YES)
        SAFE_DELETE(Info); Info=new File_ScreamTracker3();     if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_TTA_YES)
        SAFE_DELETE(Info); Info=new File_Tta();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_TWINVQ_YES)
        SAFE_DELETE(Info); Info=new File_TwinVQ();             if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_WVPK_YES)
        SAFE_DELETE(Info); Info=new File_Wvpk();               if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_XM_YES)
        SAFE_DELETE(Info); Info=new File_ExtendedModule();     if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif

    // Text
    #if defined(MEDIAINFO_N19_YES)
        SAFE_DELETE(Info); Info=new File_N19();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_PAC_YES)
        SAFE_DELETE(Info); Info=new File_Pac();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_PDF_YES)
        SAFE_DELETE(Info); Info=new File_Pdf();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_SCC_YES)
        SAFE_DELETE(Info); Info=new File_Scc();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_SDP_YES)
        SAFE_DELETE(Info); Info=new File_Sdp();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_SUBRIP_YES)
        SAFE_DELETE(Info); Info=new File_SubRip();             if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_TELETEXT_YES)
        SAFE_DELETE(Info); Info=new File_Teletext();           if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_TTML_YES)
        SAFE_DELETE(Info); Info=new File_Ttml();               if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_OTHERTEXT_YES)
        SAFE_DELETE(Info); Info=new File_OtherText();          if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif

    // Image
    #if defined(MEDIAINFO_ARRIRAW_YES)
        SAFE_DELETE(Info); Info=new File_ArriRaw();            if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_BMP_YES)
        SAFE_DELETE(Info); Info=new File_Bmp();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_BPG_YES)
        SAFE_DELETE(Info); Info=new File_Bpg();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_DDS_YES)
        SAFE_DELETE(Info); Info=new File_Dds();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_DPX_YES)
        SAFE_DELETE(Info); Info=new File_Dpx();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_GIF_YES)
        SAFE_DELETE(Info); Info=new File_Gif();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_ICO_YES)
        SAFE_DELETE(Info); Info=new File_Ico();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_JPEG_YES)
        SAFE_DELETE(Info); Info=new File_Jpeg();               if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_PCX_YES)
        SAFE_DELETE(Info); Info=new File_Pcx();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_PNG_YES)
        SAFE_DELETE(Info); Info=new File_Png();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_PSD_YES)
        SAFE_DELETE(Info); Info=new File_Psd();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_TIFF_YES)
        SAFE_DELETE(Info); Info=new File_Tiff();               if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_TGA_YES)
        //delete Info; Info=new File_Tga();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1; //At the end, too much sensible
    #endif
    #if defined(MEDIAINFO_WEBP_YES)
        SAFE_DELETE(Info); Info=new File_WebP();               if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif

    // Archive
    #if defined(MEDIAINFO_ACE_YES)
        SAFE_DELETE(Info); Info=new File_Ace();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_7Z_YES)
        SAFE_DELETE(Info); Info=new File_7z();                 if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_BZIP2_YES)
        SAFE_DELETE(Info); Info=new File_Bzip2();              if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_ELF_YES)
        SAFE_DELETE(Info); Info=new File_Elf();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_GZIP_YES)
        SAFE_DELETE(Info); Info=new File_Gzip();               if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_ISO9660_YES)
        SAFE_DELETE(Info); Info=new File_Iso9660();            if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_MACHO_YES)
        SAFE_DELETE(Info); Info=new File_MachO();              if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_MZ_YES)
        SAFE_DELETE(Info); Info=new File_Mz();                 if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_RAR_YES)
        SAFE_DELETE(Info); Info=new File_Rar();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_TAR_YES)
        SAFE_DELETE(Info); Info=new File_Tar();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_ZIP_YES)
        SAFE_DELETE(Info); Info=new File_Zip();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif

    // Other
    #if !defined(MEDIAINFO_OTHER_NO)
        SAFE_DELETE(Info); Info=new File_Other();              if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif

    //At the end, too much sensible
    #if defined(MEDIAINFO_MPEGA_YES)
        SAFE_DELETE(Info); Info=new File_Mpega();              if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_TGA_YES)
        SAFE_DELETE(Info); Info=new File_Tga();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1; //At the end, too much sensible
    #endif
    #if defined(MEDIAINFO_H263_YES)
        SAFE_DELETE(Info); Info=new File_H263();               if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_ICC_YES)
        SAFE_DELETE(Info); Info=new File_Icc();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_SPHERICALVIDEO_YES)
        SAFE_DELETE(Info); Info=new File_SphericalVideo();    if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif
    #if defined(MEDIAINFO_XMP_YES)
        SAFE_DELETE(Info); Info=new File_Xmp();                if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif

    //At the end, could load too much data for nothing
    #if defined(MEDIAINFO_ADM_YES)
        SAFE_DELETE(Info); Info=new File_Adm();               if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    #endif

    // Default (empty)
        SAFE_DELETE(Info); Info=new File_Unknown();            if (((Reader_File*)Reader)->Format_Test_PerParser(this, File_Name)>0) return 1;
    return 0;
}
#endif //!defined(MEDIAINFO_FILE_YES)

//---------------------------------------------------------------------------
bool MediaInfo_Internal::LibraryIsModified ()
{
    #if defined(MEDIAINFO_MULTI_NO) || defined(MEDIAINFO_VIDEO_NO) || defined(MEDIAINFO_AUDIO_NO) || defined(MEDIAINFO_TEXT_NO) || defined(MEDIAINFO_IMAGE_NO) || defined(MEDIAINFO_ARCHIVE_NO) \
     || defined(MEDIAINFO_BDAV_NO) || defined(MEDIAINFO_MK_NO) || defined(MEDIAINFO_OGG_NO) || defined(MEDIAINFO_RIFF_NO) || defined(MEDIAINFO_MPEG4_NO) || defined(MEDIAINFO_MPEGPS_NO) || defined(MEDIAINFO_MPEGTS_NO) || defined(MEDIAINFO_DXW_NO) || defined(MEDIAINFO_FLV_NO) || defined(MEDIAINFO_GXF_NO) || defined(MEDIAINFO_HDSF4M_NO) || defined(MEDIAINFO_HLS_NO) || defined(MEDIAINFO_ISM_NO) || defined(MEDIAINFO_IVF_NO) || defined(MEDIAINFO_LXF_NO) || defined(MEDIAINFO_SWF_NO) || defined(MEDIAINFO_MXF_NO) || defined(MEDIAINFO_NSV_NO) || defined(MEDIAINFO_NUT_NO) || defined(MEDIAINFO_WM_NO) || defined(MEDIAINFO_WTV_NO) || defined(MEDIAINFO_QT_NO) || defined(MEDIAINFO_RM_NO) || defined(MEDIAINFO_DVDIF_NO) || defined(MEDIAINFO_DVDV_NO) || defined(MEDIAINFO_AAF_NO) || defined(MEDIAINFO_CDXA_NO) || defined(MEDIAINFO_DPG_NO) || defined(MEDIAINFO_TSP_NO) \
     || defined(MEDIAINFO_AV1_NO) || defined(MEDIAINFO_AVC_NO) || defined(MEDIAINFO_AVS3V_NO) || defined(MEDIAINFO_AVSV_NO) || defined(MEDIAINFO_HEVC_NO) || defined(MEDIAINFO_MPEG4V_NO) || defined(MEDIAINFO_MPEGV_NO) || defined(MEDIAINFO_FLIC_NO) || defined(MEDIAINFO_THEORA_NO) || defined(MEDIAINFO_Y4M_NO) \
     || defined(MEDIAINFO_AC3_NO) || defined(MEDIAINFO_AC4_NO) || defined(MEDIAINFO_ADIF_NO) || defined(MEDIAINFO_ADTS_NO) || defined(MEDIAINFO_SMPTEST0337_NO) || defined(MEDIAINFO_AMR_NO) || defined(MEDIAINFO_DTS_NO) || defined(MEDIAINFO_DOLBYE_NO) || defined(MEDIAINFO_FLAC_NO) || defined(MEDIAINFO_IAMF_NO) || defined(MEDIAINFO_APE_NO) || defined(MEDIAINFO_MPC_NO) || defined(MEDIAINFO_MPCSV8_NO) || defined(MEDIAINFO_MPEGA_NO) || defined(MEDIAINFO_OPENMG_NO) || defined(MEDIAINFO_TWINVQ_NO) || defined(MEDIAINFO_XM_NO) || defined(MEDIAINFO_MOD_NO) || defined(MEDIAINFO_S3M_NO) || defined(MEDIAINFO_IT_NO) || defined(MEDIAINFO_SPEEX_NO) || defined(MEDIAINFO_TAK_NO) || defined(MEDIAINFO_PS2A_NO) \
     || defined(MEDIAINFO_CMML_NO)  || defined(MEDIAINFO_KATE_NO)  || defined(MEDIAINFO_PGS_NO) || defined(MEDIAINFO_OTHERTEXT_NO) \
     || defined(MEDIAINFO_ARRIRAW_NO) || defined(MEDIAINFO_BMP_NO) || defined(MEDIAINFO_DDS_NO) || defined(MEDIAINFO_DPX_NO) || defined(MEDIAINFO_EXR_NO) || defined(MEDIAINFO_GIF_NO) || defined(MEDIAINFO_ICO_NO) || defined(MEDIAINFO_JPEG_NO) || defined(MEDIAINFO_PNG_NO) || defined(MEDIAINFO_TGA_NO) || defined(MEDIAINFO_TIFF_NO) || defined(MEDIAINFO_WEBP_NO) \
     || defined(MEDIAINFO_7Z_NO) || defined(MEDIAINFO_ZIP_NO) || defined(MEDIAINFO_RAR_NO) || defined(MEDIAINFO_ACE_NO) || defined(MEDIAINFO_ELF_NO) || defined(MEDIAINFO_MACHO_NO) || defined(MEDIAINFO_MZ_NO) \
     || defined(MEDIAINFO_OTHER_NO) || defined(MEDIAINFO_DUMMY_NO)
        return true;
    #else
        return false;
    #endif
}

//---------------------------------------------------------------------------
void MediaInfo_Internal::CreateDummy (const String&)
{
    #if defined(MEDIAINFO_DUMMY_YES)
        Info=new File_Dummy();
        ((File_Dummy*)Info)->KindOfDummy=Value;
    #endif
}

} //NameSpace
