# UnrealDabee

A physics integration plugin for Unreal Engine that wraps the [Box3D](https://github.com/erincatto/box3d) physics library and exposes it through native UE5 components. Many features are on the way stay tuned.

## Installation

<dl>
<dd>
<dl>
<dd>

1: Clone the repo into your project's `Plugins` directory:


```bash
git clone https://github.com/LiamLeoDev/UnrealDabee.git
```

2: Right click your `.uproject` file and select **Generate Visual Studio project files**, then build the project.

<details>
<summary style="font-size: 1.1em; font-weight: bold; color:rgba(232, 127, 57, 0.86); cursor: pointer;">Troubleshooting: Box3D library errors</summary>

<dl>
<dd>
<dl>
<dd>

This shouldn't normally happen, but if you run into errors related to the Box3D library, you can rebuild it manually:

1: Download the Box3D source from [Box3D](https://github.com/erincatto/box3d).
2: From the root of that repo first build cmake project files.

```bash
cmake -B build -DBUILD_SHARED_LIBS=OFF -DBOX3D_SAMPLES=OFF -DBOX3D_UNIT_TESTS=OFF -DBOX3D_DOUBLE_PRECISION=ON
```

3: Then from  the root of that repo build Box3D.

```bash
cmake --build build --config Release
```

4: Copy the resulting `.lib`/`.a` file from `build/src/Release/` into the platform-specific directory in your plugin as `Plugins/UnrealDabee/ThirdParty/Box3D/lib/<Win|Linux|Mac>`
5: Rebuild your project — it should now compile without issues.

</dd>
</dl>
</dd>
</dl>

</details>

</dd>
</dl>
</dd>
</dl>



## Usage

- > ### **`Box3DStaticMeshComponent`**

<dl>
<dd>
<dl>
<dd>

Functions like Unreal's standard `StaticMeshComponent`. Chaos's built-in collision and physics properties are hidden in the Details panel and replaced with a dedicated <strong>Box3D</strong> category containing everything you need to configure physics for the component.

</dd>
</dl>
</dd>
</dl>

- > ### **`Box3DJointComponent`**

<dl>
<dd>
<dl>
<dd>

It is an `ActorComponent` (not a `SceneComponent`, unlike Unreal's `PhysicsConstraintComponent`). It exposes an array in its Details panel for creating multiple joints, and provides functions you can call from code to create specific joint types at runtime.

</dd>
</dl>
</dd>
</dl>

- > ### **`Box3DInstancedMeshComponent`**

<dl>
<dd>
<dl>
<dd>

Functions like Unreal's `InstancedStaticMeshComponent`, backed by Box3D physics. <strong>Currently in development</strong>
Adding instances works correctly.Removing instances does not yet remove the corresponding Box3D bodies/collisions.

</dd>
</dl>
</dd>
</dl>

## Contribution

<dl>
<dd>
<dl>
<dd>

If you find this project useful, consider giving it a ⭐ star!<br>
Contributions are welcome! If you find bugs, run into issues, or have ideas for new features, feel free to:

- Open an issue or discussion here on GitHub
- Reach out on Discord (see [Contact](#-contact))

</dd>
</dl>
</dd>
</dl>

## Contact

<dl>
<dd>
<dl>
<dd>

[![Discord](https://img.shields.io/badge/Discord-5865F2?style=for-the-badge&logo=discord&logoColor=white)](https://discord.gg/FyPv32WmHE) <br>
[![YouTube](https://img.shields.io/badge/YouTube-FF0000?style=for-the-badge&logo=youtube&logoColor=white)](https://youtube.com/@LiamLeoDev) <br>
[![X](https://img.shields.io/badge/X-000000?style=for-the-badge&logo=x&logoColor=white)](https://x.com/LiamLeo_Dev)

</dd>
</dl>
</dd>
</dl>

### License

<dl>
<dd>
<dl>
<dd>

UnrealDabee : `MIT LICENSE` <br>
Box3D&emsp;&emsp;&emsp;: `ThirdParty/Box3D/LICENSE`

</dd>
</dl>
</dd>
</dl>
