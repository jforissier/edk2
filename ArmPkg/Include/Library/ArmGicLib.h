/** @file
*
*  Copyright (c) 2011-2014, ARM Limited. All rights reserved.
*
*  This program and the accompanying materials
*  are licensed and made available under the terms and conditions of the BSD License
*  which accompanies this distribution.  The full text of the license may be found at
*  http://opensource.org/licenses/bsd-license.php
*
*  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
*  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
*
**/

#ifndef __ARMGIC_H
#define __ARMGIC_H

//
// GIC definitions
//

//
// GIC Distributor
//
#define ARM_GIC_ICDDCR          0x000 // Distributor Control Register
#define ARM_GIC_ICDICTR         0x004 // Interrupt Controller Type Register
#define ARM_GIC_ICDIIDR         0x008 // Implementer Identification Register

// Each reg base below repeats for VE_NUM_ARM_GIC_REG_PER_INT_BITS (see GIC spec)
#define ARM_GIC_ICDISR          0x080 // Interrupt Security Registers
#define ARM_GIC_ICDISER         0x100 // Interrupt Set-Enable Registers
#define ARM_GIC_ICDICER         0x180 // Interrupt Clear-Enable Registers
#define ARM_GIC_ICDSPR          0x200 // Interrupt Set-Pending Registers
#define ARM_GIC_ICDICPR         0x280 // Interrupt Clear-Pending Registers
#define ARM_GIC_ICDABR          0x300 // Active Bit Registers

// Each reg base below repeats for VE_NUM_ARM_GIC_REG_PER_INT_BYTES
#define ARM_GIC_ICDIPR          0x400 // Interrupt Priority Registers

// Each reg base below repeats for VE_NUM_ARM_GIC_INTERRUPTS
#define ARM_GIC_ICDIPTR         0x800 // Interrupt Processor Target Registers
#define ARM_GIC_ICDICFR         0xC00 // Interrupt Configuration Registers

#define ARM_GIC_ICDPPISR        0xD00 // PPI Status register

// just one of these
#define ARM_GIC_ICDSGIR         0xF00 // Software Generated Interrupt Register

//
// GIC Cpu interface
//
#define ARM_GIC_ICCICR          0x00  // CPU Interface Control Register
#define ARM_GIC_ICCPMR          0x04  // Interrupt Priority Mask Register
#define ARM_GIC_ICCBPR          0x08  // Binary Point Register
#define ARM_GIC_ICCIAR          0x0C  // Interrupt Acknowledge Register
#define ARM_GIC_ICCEIOR         0x10  // End Of Interrupt Register
#define ARM_GIC_ICCRPR          0x14  // Running Priority Register
#define ARM_GIC_ICCPIR          0x18  // Highest Pending Interrupt Register
#define ARM_GIC_ICCABPR         0x1C  // Aliased Binary Point Register
#define ARM_GIC_ICCIIDR         0xFC  // Identification Register

#define ARM_GIC_ICDSGIR_FILTER_TARGETLIST       0x0
#define ARM_GIC_ICDSGIR_FILTER_EVERYONEELSE     0x1
#define ARM_GIC_ICDSGIR_FILTER_ITSELF           0x2

// Bit-masks to configure the CPU Interface Control register
#define ARM_GIC_ICCICR_ENABLE_SECURE            0x01
#define ARM_GIC_ICCICR_ENABLE_NS                0x02
#define ARM_GIC_ICCICR_ACK_CTL                  0x04
#define ARM_GIC_ICCICR_SIGNAL_SECURE_TO_FIQ     0x08
#define ARM_GIC_ICCICR_USE_SBPR                 0x10

// Bit Mask for GICC_IIDR
#define ARM_GIC_ICCIIDR_GET_PRODUCT_ID(IccIidr)   (((IccIidr) >> 20) & 0xFFF)
#define ARM_GIC_ICCIIDR_GET_ARCH_VERSION(IccIidr) (((IccIidr) >> 16) & 0xF)
#define ARM_GIC_ICCIIDR_GET_REVISION(IccIidr)     (((IccIidr) >> 12) & 0xF)
#define ARM_GIC_ICCIIDR_GET_IMPLEMENTER(IccIidr)  ((IccIidr) & 0xFFF)

// Bit Mask for
#define ARM_GIC_ICCIAR_ACKINTID                 0x3FF

UINTN
EFIAPI
ArmGicGetInterfaceIdentification (
  IN  INTN          GicInterruptInterfaceBase
  );

//
// GIC Secure interfaces
//
VOID
EFIAPI
ArmGicSetupNonSecure (
  IN  UINTN         MpId,
  IN  INTN          GicDistributorBase,
  IN  INTN          GicInterruptInterfaceBase
  );

VOID
EFIAPI
ArmGicSetSecureInterrupts (
  IN  UINTN         GicDistributorBase,
  IN  UINTN*        GicSecureInterruptMask,
  IN  UINTN         GicSecureInterruptMaskSize
  );

VOID
EFIAPI
ArmGicEnableInterruptInterface (
  IN  INTN          GicInterruptInterfaceBase
  );

VOID
EFIAPI
ArmGicDisableInterruptInterface (
  IN  INTN          GicInterruptInterfaceBase
  );

VOID
EFIAPI
ArmGicEnableDistributor (
  IN  INTN          GicDistributorBase
  );

VOID
EFIAPI
ArmGicDisableDistributor (
  IN  INTN          GicDistributorBase
  );

UINTN
EFIAPI
ArmGicGetMaxNumInterrupts (
  IN  INTN          GicDistributorBase
  );

VOID
EFIAPI
ArmGicSendSgiTo (
  IN  INTN          GicDistributorBase,
  IN  INTN          TargetListFilter,
  IN  INTN          CPUTargetList,
  IN  INTN          SgiId
  );

UINTN
EFIAPI
ArmGicAcknowledgeInterrupt (
  IN  UINTN          GicInterruptInterfaceBase
  );

VOID
EFIAPI
ArmGicEndOfInterrupt (
  IN  UINTN                 GicInterruptInterfaceBase,
  IN UINTN                  Source
  );

UINTN
EFIAPI
ArmGicSetPriorityMask (
  IN  INTN          GicInterruptInterfaceBase,
  IN  INTN          PriorityMask
  );

VOID
EFIAPI
ArmGicEnableInterrupt (
  IN UINTN                  GicDistributorBase,
  IN UINTN                  Source
  );

VOID
EFIAPI
ArmGicDisableInterrupt (
  IN UINTN                  GicDistributorBase,
  IN UINTN                  Source
  );

BOOLEAN
EFIAPI
ArmGicIsInterruptEnabled (
  IN UINTN                  GicDistributorBase,
  IN UINTN                  Source
  );

#endif
