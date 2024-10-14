# Notes on Glk Implementations

Glk separates the functions that all interactive fiction (IF) systems have in common — such as text output, input handling, and file management — from those that depend on the operating system or device, like how text is displayed or how users interact with the game. Glk acts as the interface that bridges these two areas, allowing IF systems to work consistently across different platforms while still accommodating their unique features.

Consistent with the above description, Glk is an abstraction layer that separates the common functionality of IF systems, like TADS and Inform, from platform-specific concerns, like whether a game runs on a Mac, a terminal, or a mobile device.

Glk is essentially a cross-platform API designed to handle input/output tasks common to IF interpreters. This allows the IF game engine (e.g., for Glulx or the Z-Machine) to remain the same, while the way it interacts with the user — whether via a terminal, graphical interface, or mobile touchscreen — can vary based on the operating system or device. The game itself doesn't need to care about these details; Glk handles them.

In short, Glk provides a consistent way to manage text input/output, windowing, and file I/O across different platforms, ensuring that the user interface can be adapted without modifying the core game code.

---

The Glk spec talks about two things:

(1) the parts of the text adventure world which are identical on all IF systems, and different on different operating systems.

(2) the parts of the text adventure world which are unique to each IF system but identical in all OSs.

Breaking all that down:

(1) Parts identical across IF systems but different across operating systems: These are the common functionalities that all IF systems share, like displaying text or accepting user input. However, the way these actions are implemented can vary depending on the operating system (e.g., text rendering might differ between a terminal and a graphical interface).

(2) Parts unique to each IF system but identical across operating systems: These refer to features that are specific to each individual IF system (like TADS, Glulx, or Z-Machine), but they behave consistently no matter which platform they're running on. For example, a certain file format or game mechanic might be specific to Glulx, and it would work the same way on all operating systems, even though the way the OS handles input/output might differ.

In the case of (1), a common function across all IF systems is the need to receive user input (a command to progress the story or game). However, how that input is captured can vary widely based on the operating system or interface. That could be a command-line interface (the user types text directly into the terminal), a GUI interface (the user might type into a text box or even click buttons), or a touch interface (the user might select words or type on a virtual keyboard). What's consistent across all systems is the fact that a command is being given by the player. What's different is the method of input, which depends on the platform and the interpreter being used. Glk ensures that, regardless of the platform, the IF system can receive input in a way that's appropriate for that device or environment.

In the case of (2), the Glulx system can always generate and store a transcript of a play session — that's the behavior unique to Glulx (or another IF system) and will happen regardless of the platform. However, how the file is created, where it's stored, and what file system or format it uses will vary depending on the operating system. Glk comes into play by ensuring that the process of storing that transcript works the same from the perspective of the Glulx engine, even though the underlying file management might differ based on whether you're on a Mac, Windows, or a mobile device. So, the commonality is the feature (storing a transcript), but the OS-specific implementation (file handling) is where the variation happens.

So the idea here is that a Glk library is designed for each specific operating system or interface. For example, there could be Glk libraries for Windows, Macintosh, X-windows (used in Unix-like systems), Curses (for text-based terminal interfaces), and so on.

So let's say I'm writing a new interactive fiction interpreter, Grue. I would write the Grue engine using Glk for all input and output operations. This means my Grue engine would handle things like displaying text or accepting user input through the Glk API, but it wouldn't worry about platform-specific details like how the input is collected or how the text is rendered. Now let's consider what happens when I'm ready to release Grue on different platforms.

- For Windows, I would compile Grue and link it to a Windows-specific Glk library. This library handles all the Windows-specific interface details (like displaying text in a Windows console or GUI).
- For MacOS, I would compile Grue and link it to a MacOS Glk library, which manages things like Mac-style text input or output.
- For Linux, I would compile Grue and link it to a Linux Glk library, which could handle text output via a terminal or a graphical window like X-windows.

The key thing here is that my Grue engine stays the same across all platforms, but by linking it to the appropriate Glk library for each system, I would ensure that the game can run seamlessly on all of them. The Glk library takes care of platform-specific quirks, allowing Grue to work across operating systems without me having to rewrite the engine for each one.

The idea is that I would write the core Grue engine in a portable language, such as C, C++, or anything else that can interact with Glk. The core Grue engine would be written in portable C and would handle the core logic, rules, and mechanics of my IF system. This part would remain the same across all platforms. However, if I want to build a more sophisticated or customized user interface that fits each platform's conventions, I could have platform-specific interfaces.

- Windows: I might create a Windows interface using C++ with MFC, tailored to the Windows look and feel.
- MacOS: I could build a Mac-specific interface in Swift/Objective-C, providing a native Mac experience.

These platform-specific interfaces would interact with the portable C-based Grue engine, but each would handle platform-specific input/output, display, and user interactions in a way that feels native to the operating system. So, my Grue engine remains consistent and portable, but my interfaces can be OS-specific for a more customized experience on each platform.

---

Glk as an IF Virtual Machine: The Glk spec suggests that Glk functions similarly to how an IF virtual machine would operate, but without actually being a separate virtual machine. In this context, "virtual machine" refers to an environment designed to execute IF games, handling the mechanics and input/output operations.

Portable C Code: Instead of being a full-fledged virtual machine, Glk provides a set of portable C functions that handle I/O tasks. This means that developers can write their IF systems in C (or a compatible language) and rely on Glk to manage the way that their programs interact with the user, regardless of the platform.

Glulx: This is a specific virtual machine designed for interactive fiction that uses Glk as its interface. The Glulx VM relies on Glk calls to manage I/O operations. Each call to Glk corresponds to a specific operation within the Glulx VM, akin to how opcodes (operation codes) function in traditional virtual machines.

In essence, Glk provides the underlying functionality for managing user interactions, while Glulx is a specific implementation of an IF virtual machine that operates using that functionality. This setup allows for the separation of the game logic (handled by Glulx) from the user interface (managed by Glk), making it easier for developers to create cross-platform IF games without worrying about the underlying details of how each platform handles input and output.

So, the analogy of Glk being like an IF virtual machine is apt in that it facilitates the execution of IF games, but it's not a VM in the traditional sense; it's more about providing the necessary interface for interaction.

Thus, "Glk" or "the library" refers to the Glk library. In my example, this would be MinGlk. The "program" is the game program which is using the Glk library to print text, input text, write and read files, and so on. This would be Grue, in my example. The "player" or the "user" is the person who will use the program/Glk library combination to actually play a game or use whatever Glk-based application is provided. So, in my case, this would be someone, for example, using Grue which is linked with MinGlk.

---

The Glk API is declared in a C header file called `glk.h`.

The top level of the program – the `main()` function in C, for example – belongs to the Glk library. This is definitely different from the traditional idea of a library. This means a program linking to the Glk library must define a function called `glk_main()`. The Glk library calls `glk_main()` to begin running the program. The `glk_main()` should run until the program is finished, and then return.

To quit your own program when `glk_main()` is executing, you should call `glk_exit()`. You should only shut down your program with `glk_exit()` or by returning from your `glk_main()` function.
