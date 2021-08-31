from setuptools import find_packages, setup

setup(
    name="pyArenaPlayer",
    version="0.0.1",
    description="pyArena를 플레이할 수 있는 플레이어입니다.",
    install_requires=[],
    extras_require={},
    url="https://github.com/JYPark09/2021-HAI-RL-Arena.git",
    author="FYLSunghwan",
    author_email="sunghwan519@hotmail.com",
    packages=find_packages(exclude=["tests"]),
    entry_points={
        "console_scripts": ["pyarena = pyArenaPlayer:__main__"],
    },
)
