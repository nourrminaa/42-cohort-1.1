_This project has been created as part of the 42 curriculum by nmina._

# Born2beRoot

## Description

Born2beRoot is a system administration project that introduces virtualization by building a server from scratch inside a VM (VirtualBox/UTM). The goal is to configure a hardened, minimal Debian server: encrypted LVM partitioning, a restrictive firewall (UFW), a locked-down SSH service on a non-default port, strict password and sudo policies, proper user/group management, and a custom `monitoring.sh` script that reports system status to all terminals via `wall` on a cron schedule.

The point of the project isn't the server itself — it's understanding _why_ each configuration choice exists, since every decision (partitioning, service, policy) has to be explained and defended live.

## Instructions

### Requirements

- VirtualBox (or UTM on Apple Silicon)
- Debian (latest stable, non-testing/unstable) ISO

### Setup

1. Create a VM in VirtualBox/UTM with a minimal Debian install — **no GUI** (no X.org/Wayland).
2. During install, set up disk encryption (LUKS) and manually partition with LVM, creating at least 2 encrypted logical volumes.
3. Set hostname to `<login>42` (e.g. `nmina42`).
4. Post-install configuration:
   - Install and configure `sudo` (attempt limit, custom failure message, TTY mode, restricted `secure_path`, logging to `/var/log/sudo/`).
   - Configure password policy in `/etc/login.defs` and `pam_pwquality` (`/etc/security/pwquality.conf`).
   - Create the `<login>` user, add to `user42` and `sudo` groups.
   - Install and configure UFW, allow only port `4242`.
   - Configure SSH to listen on port `4242`, disable root login (`PermitRootLogin no`).
   - Deploy `monitoring.sh`, scheduled via `cron` (system-wide, every 10 minutes) and triggered at boot.

### Running the monitoring script

```bash
crontab -l          # view the cron schedule
sudo systemctl stop cron   # stop scheduled execution without editing the script
```

### Verifying the setup

```bash
sudo ufw status numbered        # firewall rules
sudo systemctl status ssh       # SSH service
groups <login>                  # group membership
sudo cat /etc/sudoers           # sudo policy
cat /var/log/sudo/sudo.log      # sudo action log
```

## Resources

- [Debian Documentation](https://www.debian.org/doc/)
- [VirtualBox Manual](https://www.virtualbox.org/manual/)
- [LVM HOWTO](https://tldp.org/HOWTO/LVM-HOWTO/)
- [UFW — Debian Wiki](https://wiki.debian.org/Uncomplicated%20Firewall%20%28ufw%29)
- [sudoers(5) man page](https://man.archlinux.org/man/sudoers.5)
- [AppArmor Documentation](https://wiki.debian.org/AppArmor)
- [SELinux Documentation — Red Hat](https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/9/html/using_selinux/index)
- [cron(8) man page](https://man7.org/linux/man-pages/man8/cron.8.html)

**AI disclosure:** AI (Claude) was used to structure and draft this README from project notes, and to review defense-question answers (VM concepts, Debian vs Rocky, AppArmor vs SELinux, apt vs aptitude, LVM, sudo/SSH/UFW configuration) for accuracy and completeness. All actual server configuration, partitioning, and script implementation were done manually as required by the subject's AI-use policy.

## Project Description

### Why Debian

Debian was chosen over Rocky Linux because it's the option the subject explicitly recommends for students new to system administration — Rocky requires additional SELinux configuration to meet the project's needs.

|                  | Debian                    | Rocky                               |
| ---------------- | ------------------------- | ----------------------------------- |
| Package manager  | `apt`                     | `dnf`                               |
| MAC security     | AppArmor                  | SELinux                             |
| Setup complexity | Lower                     | Higher                              |
| Focus            | Community/general-purpose | Enterprise (RHEL-compatible)        |
| Best for         | Learning, beginners       | Production, enterprise environments |

**Debian pros:** large community, stable release cycle, straightforward package management, extensive documentation, beginner-friendly.
**Debian cons:** older package versions, less enterprise tooling out of the box.

**Rocky pros:** enterprise-grade, RHEL-compatible, widely used in corporate infrastructure.
**Rocky cons:** steeper learning curve, SELinux policy configuration is significantly more involved.

### AppArmor vs SELinux

Both are Mandatory Access Control (MAC) systems that restrict what a process is allowed to do, beyond standard Unix permissions.

|                  | AppArmor             | SELinux                         |
| ---------------- | -------------------- | ------------------------------- |
| Model            | Path-based profiles  | Label-based policies            |
| Complexity       | Simpler to configure | More complex, more granular     |
| Default distro   | Debian               | Rocky/RHEL                      |
| Security ceiling | Good                 | Higher, but harder to get right |

This VM runs AppArmor (Debian's default MAC layer), enabled and running at startup as required.

### UFW vs firewalld

Both are frontends that simplify managing the kernel's packet-filtering rules (UFW wraps `iptables`/`nftables`; firewalld wraps `nftables`/`iptables` with a zone-based model).

|                | UFW                     | firewalld                          |
| -------------- | ----------------------- | ---------------------------------- |
| Distro         | Debian/Ubuntu           | RHEL/Rocky/Fedora                  |
| Model          | Simple allow/deny rules | Zone-based (trusted, public, etc.) |
| Rule changes   | Usually require reload  | Dynamic, no reload needed          |
| Learning curve | Lower                   | Higher                             |

This project uses UFW, configured to deny all incoming traffic except port `4242` (SSH).

### VirtualBox vs UTM

|                         | VirtualBox                     | UTM                               |
| ----------------------- | ------------------------------ | --------------------------------- |
| Platform                | Windows/macOS(Intel)/Linux     | macOS (esp. Apple Silicon)        |
| Virtualization backend  | Type-2 hypervisor (own engine) | QEMU + Apple Hypervisor.framework |
| Snapshot support        | Yes                            | Yes                               |
| Performance on ARM Macs | Poor/unsupported               | Native, much better               |

VirtualBox is the default and mandatory choice; UTM is the accepted fallback for Apple Silicon Macs where VirtualBox doesn't run natively.
